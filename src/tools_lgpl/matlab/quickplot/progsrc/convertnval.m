function [NVal,NValStr,NValBasic]=convertnval(NValIn)
%CONVERTNVAL Convert NVal between string and number.

%----- LGPL --------------------------------------------------------------------
%                                                                               
%   Copyright (C) 2011-2020 Stichting Deltares.                                     
%                                                                               
%   This library is free software; you can redistribute it and/or                
%   modify it under the terms of the GNU Lesser General Public                   
%   License as published by the Free Software Foundation version 2.1.                         
%                                                                               
%   This library is distributed in the hope that it will be useful,              
%   but WITHOUT ANY WARRANTY; without even the implied warranty of               
%   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU            
%   Lesser General Public License for more details.                              
%                                                                               
%   You should have received a copy of the GNU Lesser General Public             
%   License along with this library; if not, see <http://www.gnu.org/licenses/>. 
%                                                                               
%   contact: delft3d.support@deltares.nl                                         
%   Stichting Deltares                                                           
%   P.O. Box 177                                                                 
%   2600 MH Delft, The Netherlands                                               
%                                                                               
%   All indications and logos of, and references to, "Delft3D" and "Deltares"    
%   are registered trademarks of Stichting Deltares, and remain the property of  
%   Stichting Deltares. All rights reserved.                                     
%                                                                               
%-------------------------------------------------------------------------------
%   http://www.deltaressystems.com
%   $HeadURL: https://svn.oss.deltares.nl/repos/delft3d/branches/research/SANDIA/fm_tidal_v3/src/tools_lgpl/matlab/quickplot/progsrc/convertnval.m $
%   $Id: convertnval.m 65778 2020-01-14 14:07:42Z mourits $

NVal=NValIn;
NValStr=NValIn;
switch NValIn
   case -2
      NValStr='selfplotfig';
   case -1
      NValStr='selfplot';
   case 0
      NValStr='none';
   case 1
      NValStr='scalar';
   case 2
      NValStr='xy';
   case 3
      NValStr='xyz';
   case 4
      NValStr='strings';
   case 5
      NValStr='boolean';
   case 6
      NValStr='discrete';
   case 'selfplotfig'
      NVal=-2;
   case 'selfplot'
      NVal=-1;
   case 'none'
      NVal=0;
   case 'scalar'
      NVal=1;
   case {'xy','xz','xyz'}
      NVal=length(NValIn);
   case 'strings'
      NVal=4;
   case 'boolean'
      NVal=5;
   case 'discrete'
      NVal=6;
end
