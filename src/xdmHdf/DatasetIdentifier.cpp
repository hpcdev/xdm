//==============================================================================
// This software developed by Stellar Science Ltd Co and the U.S. Government.  
// Copyright (C) 2009 Stellar Science. Government-purpose rights granted.      
//                                                                             
// This file is part of XDM                                                    
//                                                                             
// This program is free software: you can redistribute it and/or modify it     
// under the terms of the GNU Lesser General Public License as published by    
// the Free Software Foundation, either version 3 of the License, or (at your  
// option) any later version.                                                  
//                                                                             
// This program is distributed in the hope that it will be useful, but WITHOUT 
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public        
// License for more details.                                                   
//                                                                             
// You should have received a copy of the GNU Lesser General Public License    
// along with this program.  If not, see <http://www.gnu.org/licenses/>.       
//                                                                             
//------------------------------------------------------------------------------
#include <xdmHdf/DatasetIdentifier.hpp>

XDM_HDF_NAMESPACE_BEGIN

xdm::RefPtr< DatasetIdentifier > createDatasetIdentifier(
  hid_t parent,
  const std::string& name,
  int type,
  hid_t dataspace ) {
  // check if the dataset already exists within the given parent
  htri_t exists = H5Lexists( parent, name.c_str(), H5P_DEFAULT );
  if ( (exists >= 0) && exists ) {
    hid_t datasetId = H5Dopen( parent, name.c_str(), H5P_DEFAULT );
    // FIXME: make sure the type and dataspace requested match those on disk.
    return xdm::RefPtr< DatasetIdentifier >( 
      new DatasetIdentifier( datasetId ) );
  }

  // the dataset doesn't exist, we create it
  hid_t datasetId = H5Dcreate(
    parent,
    name.c_str(),
    type,
    dataspace,
    H5P_DEFAULT,
    H5P_DEFAULT,
    H5P_DEFAULT );
  return xdm::RefPtr< DatasetIdentifier >( new DatasetIdentifier( datasetId ) );
}

XDM_HDF_NAMESPACE_END

