module compbsskin_module
!----- GPL ---------------------------------------------------------------------
!                                                                               
!  Copyright (C)  Stichting Deltares, 2011-2020.                                
!                                                                               
!  This program is free software: you can redistribute it and/or modify         
!  it under the terms of the GNU General Public License as published by         
!  the Free Software Foundation version 3.                                      
!                                                                               
!  This program is distributed in the hope that it will be useful,              
!  but WITHOUT ANY WARRANTY; without even the implied warranty of               
!  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
!  GNU General Public License for more details.                                 
!                                                                               
!  You should have received a copy of the GNU General Public License            
!  along with this program.  If not, see <http://www.gnu.org/licenses/>.        
!                                                                               
!  contact: delft3d.support@deltares.nl                                         
!  Stichting Deltares                                                           
!  P.O. Box 177                                                                 
!  2600 MH Delft, The Netherlands                                               
!                                                                               
!  All indications and logos of, and references to, "Delft3D" and "Deltares"    
!  are registered trademarks of Stichting Deltares, and remain the property of  
!  Stichting Deltares. All rights reserved.                                     
!                                                                               
!-------------------------------------------------------------------------------
!  $Id: compbsskin.f90 65875 2020-01-28 09:57:58Z j.reyns $
!  $HeadURL: https://svn.oss.deltares.nl/repos/delft3d/branches/research/SANDIA/fm_tidal_v3/src/utils_gpl/morphology/packages/morphology_kernel/src/compbsskin.f90 $
!-------------------------------------------------------------------------------

contains

subroutine compbsskin (umean , vmean , depth , wave  , uorb  , tper  , &
                     & teta  , thcmud, mudfrac, taumax, rhowat, vicmol, &
                     & sedpar)
!!--description-----------------------------------------------------------------
!
! Compute tau in case of muddy bed (skin fraction  only)
! Soulsby  (2004)
!
! Remarks: 1) uorb based upon Hrms, Tper = peak period wave spectrum
!          2) skin friction comuted and used everywhere in the model
!             (not yet a distinction based upon md layer thickness or
!              mudcontent)
!          4) umean and vmean based upon u0eul, v0eul (inclding wave mass fluxes)
!          5) ar = 0.26; as = 0.22 (original publication soulsby)
!          6) taumax or taum used in erosion/sedimentation computations ????????
!          7) Smooth bed formulations explode in case of
!             small orbital velocities (0.0001 m/s). Set orbital velocity to
!             at least 1 cm/s
!          8) Mutiple mud fractions, each fraction own kssilt and kssand?????
!
!!--declarations----------------------------------------------------------------
    use precision
    use mathconsts
    use morphology_data_module, only:sedpar_type, SC_MUDFRAC
    !
    implicit none
!
! Local parameters
!
    real(fp), parameter :: localeps = 1.0e-12_fp
!
! Global variables
!
    real(fp)         , intent(in)  :: umean   ! depth averaged flow velocity in u-direction
    real(fp)         , intent(in)  :: vmean   ! depth averaged flow velocity in v-direction
    real(fp)         , intent(in)  :: depth   ! local water depth
    real(fp)         , intent(in)  :: uorb    ! orbital velocity based upon Hrms
    real(fp)         , intent(in)  :: tper    ! wave period
    real(fp)         , intent(in)  :: teta    ! angle between wave direction and local
                                              ! grid orientation
    real(fp)         , intent(in)  :: thcmud  ! Total hickness of mud layers
    real(fp)         , intent(in)  :: mudfrac ! Total mud fraction in top layer
    real(fp)         , intent(out) :: taumax  ! resulting (maximum) bed shear stress muddy silt bed
    logical          , intent(in)  :: wave    ! wave impacts included in flow comp. or not
    real(fp)         , intent(in)  :: rhowat  ! water density
    real(fp)         , intent(in)  :: vicmol  ! molecular viscosity
    type(sedpar_type), target      :: sedpar
!
! Local variables
!
    real(fp) :: a1      ! Help variable
    real(fp) :: a2      ! Help variable
    real(fp) :: alpha   ! Help variable
    real(fp) :: ar      ! Constant rough  bed turbulent flow
    real(fp) :: as      ! Constant smooth bed turbulent flow
    real(fp) :: aorb    ! Orbital displacement
    real(fp) :: cdr     ! Drag coefficient rough  turbulent flows
    real(fp) :: cdm     ! Mean drag coefficient (current)
    real(fp) :: cds     ! Drag coefficient smooth turbulent flows
    real(fp) :: cdmax   ! Drag coefficient (current + waves)
    real(fp) :: fws     ! Wave friction coeefficient smooth turbulent flows
    real(fp) :: fwr     ! Wave friction coeefficient rough  turbulent flows
    real(fp) :: mudfac  ! Characteristic mud factor (fraction or thickness)
    real(fp) :: phicur  ! Angle beteen mean flow and local grid orientation
    real(fp) :: phiwr   ! Angle beteen flow and wave direction
    real(fp) :: rec     ! Reynolds number flow
    real(fp) :: reccr   ! Critcal Reynolds number current
    real(fp) :: rew     ! Reynolds number waves
    real(fp) :: rewcr   ! Critcal Reynolds number waves
    real(fp) :: taum    ! Mean shear stress
    real(fp) :: tauw    ! Shear stress (waves)
    real(fp) :: taumr   ! Mean shear stress (rough  bed)
    real(fp) :: taums   ! Mean shear stress (smooth bed)
    real(fp) :: taumaxr ! Maximum shear stress (rough  bed)
    real(fp) :: taumaxs ! Maximum shear stress (smooth bed)
    real(fp) :: t1      ! Help variable
    real(fp) :: t2      ! Help variable
    real(fp) :: t3      ! Help variable
    real(fp) :: umod    ! Magnitude depth averaged flow velocity
    real(fp) :: uorbm   ! Maximum uorb and 1 cm/s
    real(fp) :: z0silt  ! Roughness height
    !
    integer , pointer :: sc_mudfac  ! flag variable indicating mud factor
    real(fp), pointer :: kssilt     ! roughness height silt
    real(fp), pointer :: kssand     ! roughness height sand
    real(fp), pointer :: sc_cmf1    ! critical mud factor
    real(fp), pointer :: sc_cmf2    ! critical mud factor
!
!! executable statements -------------------------------------------------------
!
    sc_mudfac => sedpar%sc_mudfac
    kssilt    => sedpar%kssilt
    kssand    => sedpar%kssand
    sc_cmf1   => sedpar%sc_cmf1
    sc_cmf2   => sedpar%sc_cmf2
    !
    ! Set constants
    !
    ar    = 0.24_fp
    as    = 0.24_fp
    rewcr = 1.5e5_fp
    !
    ! Compute basic parameters
    !
    umod   = max( sqrt(umean*umean + vmean*vmean) , localeps )
    !
    if (sc_mudfac == SC_MUDFRAC) then
       mudfac = mudfrac
    else
       mudfac = thcmud
    endif
    if (mudfac > sc_cmf2) then
       alpha = 1.0_fp
    elseif (mudfac > sc_cmf1) then
       alpha = (mudfac - sc_cmf1) / (sc_cmf2 - sc_cmf1)
       alpha = 3.0_fp * alpha**2 - 2.0_fp * alpha**3
    else
       alpha = 0.0_fp
    endif
    z0silt = max( (alpha*kssilt+(1.0_fp-alpha)*kssand)/30.0_fp , localeps )
    !
    rec    = umod * depth / vicmol
    cds    = 1.615e-4_fp * exp(6.0_fp * rec**(-0.08_fp))
    cdr    = ( 0.40_fp / (log(depth/z0silt)-1.0_fp) )**2
    phicur = atan2(vmean,umean) / degrad
    if (phicur < 0.0_fp) phicur = phicur + 360.0_fp
    !
    if (wave) then
       phiwr  = (teta - phicur) * degrad
       uorbm  = max( uorb , 0.01_fp )
       aorb   = uorbm * tper / 2.0_fp / pi
       rew    = max(uorbm * aorb / vicmol, 1e3_fp) ! limit rew to avoid t1->1 and a1,a2->Inf in computation of taums 
       fws    = 0.0521_fp * rew**(-0.187_fp)
       fwr    = 1.39_fp * (aorb/z0silt)**(-0.52_fp)
    endif
    !
    ! Determine flow regime
    !
    if (wave .and. uorb >= 1.0-6_fp) then
       if (umod >= 1.0e-6_fp) then
          !
          ! Combined flow and waves
          !
          reccr = 2000.0_fp + (5.92e5_fp * rew)**0.35_fp
          if (rec <= reccr .and. rew <= rewcr) then
             !
             ! laminar flow
             !
             taum   = 3.0_fp * rhowat * vicmol * umod / depth
             tauw   = rhowat * uorbm * uorbm / sqrt(rew)
             taumax = sqrt((taum +  tauw*abs(cos(phiwr)))**2 &
                          &      + (tauw*abs(sin(phiwr)))**2 )
          else
             !
             ! turbulent flow
             !
             ! 1) compute shear stresses belonging with rough bed
             !
             t1      = max(12.0_fp , ar * sqrt(fwr/2.0_fp) * (aorb/z0silt))
             t2      = depth / (t1 * z0silt)
             t3      = (cdr*cdr + (fwr/2.0_fp)**2 * (uorbm/umod)**4)**0.25_fp
             !
             a1      = t3 * (log(t2) - 1.0_fp) / (2.0_fp*log(t1))
             a2      = 0.40_fp * t3 / log(t1)
             cdm     = (sqrt(a1*a1 + a2) - a1)**2
             cdmax   = sqrt((cdm +  t3*(uorbm/umod)*sqrt(fwr/2.0_fp)*abs(cos(phiwr)))**2 &
                            &    + (t3*(uorbm/umod)*sqrt(fwr/2.0_fp)*abs(sin(phiwr)))**2 )
             taumr   = rhowat * cdm   * umod * umod
             taumaxr = rhowat * cdmax * umod * umod
             !
             ! 2) compute shear stresses belonging with smooth bed
             !
             t1      = 9.0_fp * as * rew * sqrt(fws/2.0_fp) &
                     & * (cds*cds*(umod/uorbm)**4 + (fws/2.0_fp)**2)**0.25_fp
             t2      = ( (rec/rew)*(uorbm/umod)*sqrt(2.0_fp/fws) ) / as
             t3      = (cds*cds + (fws/2.0_fp)**2 * (uorbm/umod)**4)**0.25_fp
             !
             a1      = t3 * (log(t2) - 1.0_fp) / (2.0_fp*log(t1))
             a2      = 0.40_fp * t3 / log(t1)
             cdm     = (sqrt(a1*a1 + a2) - a1)**2
             cdmax   = sqrt((cdm +  t3*(uorbm/umod)*sqrt(fws/2.0_fp)*abs(cos(phiwr)))**2 &
                            &    + (t3*(uorbm/umod)*sqrt(fws/2.0_fp)*abs(sin(phiwr)))**2)
             taums   = rhowat * cdm   * umod * umod
             taumaxs = rhowat * cdmax * umod * umod
             !
             ! 3) determine shear stresses
             !
             if (taumaxs > taumaxr) then
                taum   = taums
                taumax = taumaxs
             else
                taum   = taumr
                taumax = taumaxr
             endif
          endif
       else
          !
          ! Waves only
          !
          taum = 0.0_fp
          if (rew <= rewcr) then
             taumax = rhowat * uorbm * uorbm / sqrt(rew)
          else
             if (fwr >= fws) then
                taumax = 0.5_fp * rhowat * fwr * uorbm * uorbm
             else
                taumax = 0.5_fp * rhowat * fws * uorbm * uorbm
             endif
          endif
       endif
    elseif (umod >= 1.0e-6_fp) then
       !
       ! Flow only
       !
       if (rec <= 2000.0_fp) then
          taum   = 3.0_fp * rhowat * vicmol * umod / depth
          taumax = taum
       else
          if (cdr >= cds) then
             taum = rhowat * cdr * umod * umod
          else
             taum = rhowat * cds * umod * umod
          endif
          taumax = taum
       endif
    else
       !
       ! No flow and no waves
       !
       taum   = 0.0_fp
       taumax = 0.0_fp
    endif
end subroutine compbsskin

end module compbsskin_module
