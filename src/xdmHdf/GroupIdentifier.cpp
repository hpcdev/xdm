#include <xdmHdf/GroupIdentifier.hpp>

XDM_HDF_NAMESPACE_BEGIN

xdm::RefPtr< GroupIdentifier > createGroupIdentifier(
  hid_t parent, const std::string& name ) {
  // check if the group already exists within the parent
  htri_t exists = H5Lexists( parent, name.c_str(), H5P_DEFAULT );
  if ( (exists>=0) && exists ) {
    hid_t groupId = H5Gopen( parent, name.c_str(), H5P_DEFAULT );
    return xdm::RefPtr< GroupIdentifier >( new GroupIdentifier( groupId ) );
  }

  // it doesn't already exist, create it
  hid_t groupId = H5Gcreate( 
    parent, 
    name.c_str(), 
    H5P_DEFAULT, 
    H5P_DEFAULT,
    H5P_DEFAULT );
  return xdm::RefPtr< GroupIdentifier >( new GroupIdentifier( groupId ) );
}

XDM_HDF_NAMESPACE_END

