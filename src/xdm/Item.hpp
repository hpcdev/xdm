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
#ifndef xdm_Item_hpp
#define xdm_Item_hpp

#include <xdm/ReferencedObject.hpp>
#include <xdm/ThrowMacro.hpp>
#include <xdm/XmlMetadataWrapper.hpp>

#include <stdexcept>
#include <string>

#include <xdm/NamespaceMacro.hpp>

/// Macro to assist classes in defining boilerplate functions that are
/// helpful when subclassing Item.  This macro will provide the correct
/// defintions of className() and accept(ItemVisitor&).
#define XDM_META_ITEM( name ) \
  virtual const char* className() const { return #name; } \
  virtual void accept( xdm::ItemVisitor& iv ) { iv.apply( *this ); }

XDM_NAMESPACE_BEGIN

class Item;
class ItemVisitor;

/// Callback class for updating a generic Item dynamically. These callbacks
/// can be attached to items in the xdm data tree to add behavior that is
/// called during an update traversal of the data tree.
/// @see UpdateVisitor
class BasicItemUpdateCallback : public ReferencedObject {
public:
  /// Update the Item during an update traversal. This method provides a
  /// customization point for library clients to define custom update behavior
  /// for an object.
  virtual void update( Item& item ) = 0;
};

/// BasicItemUpdateCallback that uses the template argument to pass a concrete
/// subclass of Item into the update call. This can be used to define a type
/// safe callback that will apply only to a specific subclass of Item.
/// @param ItemT The concrete subclass of Item to act on.
template< typename ItemT >
class ItemUpdateCallback : public BasicItemUpdateCallback {
public:
  /// Update the Item if it is a subclass of both Item and the template
  /// parameter. If the Item is not a subclass of the template parameter, an
  /// exception will be thrown.
  void update( Item& item ) {
    try {
      ItemT& typedItem = dynamic_cast< ItemT& >( item );
      this->update( typedItem );
    } catch ( std::bad_cast ) {
      XDM_THROW( std::runtime_error( "Invalid Item type for callback" ) );
    }
  }

  /// Update the specific subclass of Dataset that the callback is designed to
  /// operate upon.
  virtual void update( ItemT* dataset ) = 0;
};

/// Base class for all elements of the data hierarchy.
class Item : public ReferencedObject {
public:
  Item();
  virtual ~Item();

  void setName( const std::string& name );
  const std::string& name() const;

  /// Subclasses should override to return their specific type.
  virtual const char * className() const;

  //-- Visitor Traversal Interface --//
  
  /// Accept a visitor, calling its apply with my type as input.
  virtual void accept( ItemVisitor& iv );
  /// Define the traversal for an item.  The visitor will choose when,
  /// subclasses of item tell it how.
  virtual void traverse( ItemVisitor& );

  //-- End Visitor Traversal Interface --//

  /// Get the Item's update callback.
  RefPtr< BasicItemUpdateCallback > updateCallback();
  /// Get the Item's const update callback.
  RefPtr< const BasicItemUpdateCallback > updateCallback() const;
  /// Set the Item's update callback.
  void setUpdateCallback( RefPtr< BasicItemUpdateCallback > callback );

  /// Write an Item's metadata to an XmlObject.  NOTE: implementors should *NOT*
  /// write data for child objects to the input XmlObject.  That responsibility
  /// is reserved for visitor classes so that the communication, memory
  /// referencing, and cacheing can be managed by client applications.
  virtual void writeMetadata( XmlMetadataWrapper& metadata );

private:
  std::string mName;
  RefPtr< BasicItemUpdateCallback > mUpdateCallback;
};

XDM_NAMESPACE_END

#endif // xdm_Item_hpp

