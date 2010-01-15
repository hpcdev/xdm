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
#ifndef xdm_ReferencedObject_hpp
#define xdm_ReferencedObject_hpp

#include <cstdlib>

#include <xdm/NamespaceMacro.hpp>

XDM_NAMESPACE_BEGIN

/// Base class for all reference counted objects.
class ReferencedObject {
public:
  ReferencedObject();
  virtual ~ReferencedObject();

  /// Add a reference to this object.
  void addReference();

  /// Remove a reference from this object.  When the reference count goes to
  /// zero, the object will be deleted.
  void removeReference();
  /// Remove a reference without checking the reference count.
  void removeReferenceWithoutDelete();
  /// Get the current reference count for an object.
  int referenceCount() const;

private:
  int mReferenceCount;
};

XDM_NAMESPACE_END

#endif // xdm_ReferencedObject_hpp

