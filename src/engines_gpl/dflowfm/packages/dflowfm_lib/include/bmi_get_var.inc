!----- AGPL --------------------------------------------------------------------
!                                                                               
!  Copyright (C)  Stichting Deltares, 2015-2018.                                
!                                                                               
!  This file is part of Delft3D (D-Flow Flexible Mesh component).               
!                                                                               
!  Delft3D is free software: you can redistribute it and/or modify              
!  it under the terms of the GNU Affero General Public License as               
!  published by the Free Software Foundation version 3.                         
!                                                                               
!  Delft3D  is distributed in the hope that it will be useful,                  
!  but WITHOUT ANY WARRANTY; without even the implied warranty of               
!  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
!  GNU Affero General Public License for more details.                          
!                                                                               
!  You should have received a copy of the GNU Affero General Public License     
!  along with Delft3D.  If not, see <http://www.gnu.org/licenses/>.             
!                                                                               
!  contact: delft3d.support@deltares.nl                                         
!  Stichting Deltares                                                           
!  P.O. Box 177                                                                 
!  2600 MH Delft, The Netherlands                                               
!                                                                               
!  All indications and logos of, and references to, "Delft3D",                  
!  "D-Flow Flexible Mesh" and "Deltares" are registered trademarks of Stichting 
!  Deltares, and remain the property of Stichting Deltares. All rights reserved.
!                                                                               
!-------------------------------------------------------------------------------

  select case(var_name)
  case("DFM_COMM_DFMWORLD") !<  [-] The MPI communicator for dflowfm (FORTRAN handle). {"rank": 0}
     x = c_loc(DFM_COMM_DFMWORLD)
  case("iglobal_s") !<  [-] global flow node numbers to help output aggregation later. Should exactly correspond with the original unpartitioned flow node numbers! (as opposed to iglobal) {"shape": ["ndx"]}
     x = c_loc(iglobal_s)
  case("twav") !<  [s] wave period {"location": "face", "shape": ["ndx"]}
     x = c_loc(twav)
  case("Uorb") !<  [m/s] orbital velocity {"location": "face", "shape": ["ndx"]}
     x = c_loc(Uorb)
  case("shx") !<  [m] current position {"shape": ["nshiptxy"]}
     x = c_loc(shx)
  case("shy") !<  [m] current position {"shape": ["nshiptxy"]}
     x = c_loc(shy)
  case("shi") !<  [m] current position {"shape": ["nshiptxy"]}
     x = c_loc(shi)
  case("zsp") !<  [m] ship depth at flownodes {"shape": ["ndx"]}
     x = c_loc(zsp)
  case("zsp0") !<  [m] ship depth at flownodes prev step {"shape": ["ndx"]}
     x = c_loc(zsp0)
  case("zspc") !<  [m] ship depth at netnodes {"shape": ["numk"]}
     x = c_loc(zspc)
  case("zspc0") !<  [m] ship depth at netnodes {"shape": ["numk"]}
     x = c_loc(zspc0)
  case("v0ship") !<  [m] ship 0 volume {"shape": ["ndx"]}
     x = c_loc(v0ship)
  case("v1ship") !<  [m] ship 1 volume {"shape": ["ndx"]}
     x = c_loc(v1ship)
  case("qinship") !<  [m] ship flux (v1-v0)/dt {"shape": ["ndx"]}
     x = c_loc(qinship)
  case("vicushp") !<  [m] eddyvisc ship {"shape": ["lnx"]}
     x = c_loc(vicushp)
  case("vos") !<  [m] ship link volume bob like {"shape": ["2","lnx"]}
     x = c_loc(vos)
  case("shL") !<  [m] ship size L/2, B/2, D  ! for now, fixed max nr =2 {"shape": [2]}
     x = c_loc(shL)
  case("shB") !<  [m] ship size L/2, B/2, D  ! for now, fixed max nr =2 {"shape": [2]}
     x = c_loc(shB)
  case("shd") !<  [m] ship size L/2, B/2, D  ! for now, fixed max nr =2 {"shape": [2]}
     x = c_loc(shd)
  case("stuw") !<  [N] actual thrust force in ship dir {"shape": [2]}
     x = c_loc(stuw)
  case("fstuw") !<  [-] thrust setting 0-1 {"shape": [2]}
     x = c_loc(fstuw)
  case("stuwmx") !<  [N] max thrust {"shape": [2]}
     x = c_loc(stuwmx)
  case("roer") !<  [degree] actual rudder angle {"shape": [2]}
     x = c_loc(roer)
  case("froer") !<  [degree] actual rudder setting 0-1 {"shape": [2]}
     x = c_loc(froer)
  case("roermx") !<  [degree] max rudder angle {"shape": [2]}
     x = c_loc(roermx)
  case("wx") !<  [m/s] wind x velocity   (m/s) at u point {"location": "edge", "shape": ["lnx"]}
     x = c_loc(wx)
  case("wy") !<  [m/s] wind y velocity   (m/s) at u point {"location": "edge", "shape": ["lnx"]}
     x = c_loc(wy)
  case("wmag") !<  [m/s] wind magnitude    (m/s) at u point {"location": "edge", "shape": ["lnx"]}
     x = c_loc(wmag)
  case("rain") !<  [mm/day] rain at xz,yz {"location": "face", "shape": ["ndx"]}
     x = c_loc(rain)
  case("evap") !<  [m/s] evaporation at xz,yz {"location": "face", "shape": ["ndx"]}
     x = c_loc(evap)
  case("rnveg") !<  [1/m2] 3D plant density , 2D part is basis input (1/m2) {"location": "face", "shape": ["ndkx"]}
     x = c_loc(rnveg)
  case("diaveg") !<  [m] 3D plant diameter, 2D part is basis input (m) {"location": "face", "shape": ["ndkx"]}
     x = c_loc(diaveg)
  case("cfuveg") !<  [ ] 2D only, g/C2 in 2D such that bedstress is computed correctly {"location": "face", "shape": ["lnx"]}
     x = c_loc(cfuveg)
  case("alfaveg") !<  [1/m] 2D only, stem contribution {"location": "face", "shape": ["lnx"]}
     x = c_loc(alfaveg)
  case("stemdens") !<  [1/m2] TEMP 2D plant density (1/m2) {"location": "face", "shape": ["ndx"]}
     x = c_loc(stemdens)
  case("stemdiam") !<  [m] TEMP 2D plant diameters (m) {"location": "face", "shape": ["ndx"]}
     x = c_loc(stemdiam)
  case("stemheight") !<  [m] 2D plant heights (m) {"location": "face", "shape": ["ndx"]}
     x = c_loc(stemheight)
  case("zws") !<  [m] z levels  (m) of interfaces (w-points) at cell centres (s-points) (m)    (1:ndkx) {"shape": ["ndkx"]}
     x = c_loc(zws)
  case("kbot") !<  [-] layer-compressed bottom layer cell number: for each of ndx horizontal cells, we have indices to bot and top ndxk cells {"location": "face", "shape": ["ndx"]}
     x = c_loc(kbot)
  case("ktop") !<  [-] layer-compressed top layer cell number: for each of ndx horizontal cells, we have indices to bot and top ndxk cells {"location": "face", "shape": ["ndx"]}
     x = c_loc(ktop)
  case("Lbot") !<  [-] layer-compressed bottom layer edge number: for each of lnx horizontal links, we have indices to bot and top lnxk links {"location": "edge", "shape": ["lnx"]}
     x = c_loc(Lbot)
  case("Ltop") !<  [-] layer-compressed top layer edge number: for each of lnx horizontal links, we have indices to bot and top lnxk links {"location": "edge", "shape": ["lnx"]}
     x = c_loc(Ltop)
  case("s0") !<  [m] waterlevel    (m ) at start of timestep {"location": "face", "shape": ["ndx"]}
     x = c_loc(s0)
  case("s1") !<  [m] waterlevel    (m ) at end   of timestep {"location": "face", "shape": ["ndx"]}
     x = c_loc(s1)
  case("a0") !<  [m2] storage area at start of timestep {"location": "face", "shape": ["ndx"]}
     x = c_loc(a0)
  case("a1") !<  [m2] storage area at end of timestep {"location": "face", "shape": ["ndx"]}
     x = c_loc(a1)
  case("vol0") !<  [m3] volume at start of timestep {"location": "face", "shape": ["ndx"]}
     x = c_loc(vol0)
  case("vol1") !<  [m3] volume at end of timestep {"location": "face", "shape": ["ndx"]}
     x = c_loc(vol1)
  case("hs") !<  [m] waterdepth at cell centre = s1 - bl  (m) {"location": "face", "shape": ["ndx"]}
     x = c_loc(hs)
  case("ucx") !<  [m/s] cell center velocity, global x-dir (m/s) {"location": "face", "shape": ["ndkx"]}
     x = c_loc(ucx)
  case("ucy") !<  [m/s] cell center velocity, global y-dir (m/s) {"location": "face", "shape": ["ndkx"]}
     x = c_loc(ucy)
  case("ucz") !<  [m/s] cell center velocity, global z-dir (m/s) {"location": "face", "shape": ["ndkx"]}
     x = c_loc(ucz)
  case("sa0") !<  [1e-3] salinity (ppt) at start of timestep {"location": "face", "shape": ["ndkx"]}
     x = c_loc(sa0)
  case("sa1") !<  [1e-3] salinity (ppt) at end   of timestep {"location": "face", "shape": ["ndkx"]}
     x = c_loc(sa1)
  case("satop") !<  [1e-3] salinity (ppt) help in initialise , deallocated {"location": "face", "shape": ["ndx"]}
     x = c_loc(satop)
  case("tem0") !<  [degC] water temperature at end of timestep {"location": "face", "shape": ["ndkx"]}
     x = c_loc(tem0)
  case("tem1") !<  [degC] water temperature at end of timestep {"location": "face", "shape": ["ndkx"]}
     x = c_loc(tem1)
  case("u1") !<  [m/s] flow velocity (m/s)  at   end of timestep {"location": "edge", "shape": ["lnkx"]}
     x = c_loc(u1)
  case("q1") !<  [m3/s] discharge     (m3/s) at   end of timestep n, used as q0 in timestep n+1, statement q0 = q1 is out of code, saves 1 array {"location": "edge", "shape": ["lnkx"]}
     x = c_loc(q1)
  case("au") !<  [m2] flow area     (m2)   at u point {"location": "edge", "shape": ["lnkx"]}
     x = c_loc(au)
  case("hu") !<  [m] upwind waterheight at u-point (m) {"location": "edge", "shape": ["lnx"]}
     x = c_loc(hu)
  case("frcu") !<  [TODO] friction coefficient set by initial fields {"location": "edge", "shape": ["lnx"]}
     x = c_loc(frcu)
  case("viusp") !<  [m2/s] user defined spatial eddy viscosity coefficient at u point (m2/s) {"location": "edge", "shape": ["lnx"]}
     x = c_loc(viusp)
  case("diusp") !<  [m2/s] user defined spatial eddy diffusivity coefficient at u point (m2/s) {"location": "edge", "shape": ["lnx"]}
     x = c_loc(diusp)
  case("ndx2d") !<  [-] Number of 2D flow cells (= NUMP). {"rank": 0}
     x = c_loc(ndx2d)
  case("ndxi") !<  [-] Number of internal flowcells  (internal = 2D + 1D ). {"rank": 0}
     x = c_loc(ndxi)
  case("ndx1db") !<  [-] Number of flow nodes incl. 1D bnds (internal 2D+1D + 1D bnd). {"rank": 0}
     x = c_loc(ndx1db)
  case("ndx") !<  [-] Number of flow nodes (internal + boundary). {"rank": 0}
     x = c_loc(ndx)
  case("kfs") !<  [-] node code flooding {"shape": ["ndx"]}
     x = c_loc(kfs)
  case("kfst0") !<  [-] node code flooding {"shape": ["ndx"]}
     x = c_loc(kfst0)
  case("ba") !<  [m2] bottom area, if < 0 use table in node type {"location": "face", "shape": ["ndx"]}
     x = c_loc(ba)
  case("bl") !<  [m] bottom level (m) (positive upward) {"location": "face", "shape": ["ndx"]}
     x = c_loc(bl)
  case("xz") !<  [m/degrees_east] waterlevel point / cell centre, x-coordinate (m) {"location": "face", "shape": ["ndx"]}
     x = c_loc(xz)
  case("yz") !<  [m/degrees_north] waterlevel point / cell centre, y-coordinate (m) {"location": "face", "shape": ["ndx"]}
     x = c_loc(yz)
  case("lnx1D") !<  [-] nr of 1D flow links (so first 1D, next 2D, next boundaries). {"rank": 0}
     x = c_loc(lnx1D)
  case("lnxi") !<  [-] nr of flow links (internal, 1D+2D    ). {"rank": 0}
     x = c_loc(lnxi)
  case("lnx1Db") !<  [-] nr of flow links including 1D bnds (internal, 1D+2D, boundary: only 1D. 2D bnd behind it). {"rank": 0}
     x = c_loc(lnx1Db)
  case("lnx") !<  [-] nr of flow links (internal + boundary). First we have 1D links, next 2D links, next boundary links (first 1D, then 2D). {"rank": 0}
     x = c_loc(lnx)
  case("ln") !<  [-] 1D link (2,*) node   administration, 1=nd1,  2=nd2   linker en rechter celnr {"shape": [2, "lnkx"]}
     x = c_loc(ln)
  case("lncn") !<  [-] 2D link (2,*) corner administration, 1=nod1, 2=nod2  linker en rechter netnr {"shape": [2, "lnkx"]}
     x = c_loc(lncn)
  case("iadv") !<  [-] type of advection for this link {"location": "edge", "shape": ["lnx"]}
     x = c_loc(iadv)
  case("dx") !<  [m] link length (m) {"location": "edge", "shape": ["lnx"]}
     x = c_loc(dx)
  case("wu") !<  [m] link initial width (m), if < 0 pointer to convtab {"location": "edge", "shape": ["lnx"]}
     x = c_loc(wu)
  case("bob") !<  [m] left and right inside lowerside tube (binnenkant onderkant buis) HEIGHT values (m) (positive upward) {"location": "edge", "shape": [2, "lnx"]}
     x = c_loc(bob)
  case("vort") !<  [s-1] vorticity at netnodes {"shape": ["ndx"], "comment": "Currently not available, is nowhere allocated nor filled."}
     x = c_loc(vort)
  case("xzw") !<  [m] centre of gravity {"shape": ["nump"]}
     x = c_loc(xzw)
  case("yzw") !<  [m] centre of gravity {"shape": ["nump"]}
     x = c_loc(yzw)
  case("xk") !<  [-] Net node x coordinate {"shape": ["numk"]}
     x = c_loc(xk)
  case("yk") !<  [-] Net node y coordinate {"shape": ["numk"]}
     x = c_loc(yk)
  case("zk") !<  [-] Net node z coordinate {"shape": ["numk"]}
     x = c_loc(zk)
  case("kn") !<  [-] Net links: kn(1,:)=from-idx, kn(2,:)=to-idx, kn(3,:)=net link type (0/1/2/3/4) {"shape": [3, "numl"]}
     x = c_loc(kn)
  case("numk") !<  [-] Nr. of net nodes. {"shape": []}
     x = c_loc(numk)
  case("zbnd1d2d1") !<  [m] 1d2d boundary points 1d water level at new time level {"shape": ["nbnd1d2d"]}
     x = c_loc(zbnd1d2d1)
  case("zbnd1d2d0") !<  [m] 1d2d boundary points 1d water level at previous time level {"shape": ["nbnd1d2d"]}
     x = c_loc(zbnd1d2d0)
  case("zcrest1d2d") !<  [m] 1d2d helper array with crest levels {"shape": ["nbnd1d2d"]}
     x = c_loc(zcrest1d2d)
  case("edgenumbers1d2d") !<  [m] 1d2d helper array with edge numbers {"shape": ["nbnd1d2d"]}
     x = c_loc(edgenumbers1d2d)
  case("kbnd1d2d") !<  [-] 1d2d boundary points index array {"shape": ["5","nbnd1d2d"]}
     x = c_loc(kbnd1d2d)
  case("width_1d") !<  [m] width 1D SOBEK channel --2D FM coupling {"shape": ["nbnd1d2d"]}
     x = c_loc(width_1d)
  case("qzeta_1d2d") !<  [m3 s-1] 1d2d output array via BMI for qzeta in 1D SOBEK--2D FM coupling {"shape": ["nbnd1d2d"]}
     x = c_loc(qzeta_1d2d)
  case("qlat_1d2d") !<  [m3 s-1] 1d2d output array via BMI for qlat in 1D SOBEK--2D FM coupling {"shape": ["nbnd1d2d"]}
     x = c_loc(qlat_1d2d)
  case("qtotal_1d2d") !<  [m3 s-1] 1d2d output array via BMI for qlat in 1D SOBEK--2D FM coupling {"shape": ["nbnd1d2d"]}
     x = c_loc(qtotal_1d2d)
  case("is_sumvalsnd") !<  [-] Integral values on flow nodes. {"location": "face", "shape": ["is_numndvals", "ndx"]}
     x = c_loc(is_sumvalsnd)
  case("is_maxvalsnd") !<  [-] Integral values on flow nodes. {"location": "face", "shape": ["is_numndvals", "ndx"]}
     x = c_loc(is_maxvalsnd)
  case("is_dtint") !<  [s] total time interval since last statistics reset. {"rank": 0}
     x = c_loc(is_dtint)
  end select
