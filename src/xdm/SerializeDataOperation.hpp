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
#ifndef xdm_SerializeDataOperation_hpp
#define xdm_SerializeDataOperation_hpp

#include <xdm/Dataset.hpp>
#include <xdm/ItemVisitor.hpp>



namespace xdm {

class UniformDataItem;

/// Operation defined on the data tree that serializes all datasets it
/// encounters.  Implements the ItemVisitor interface to find all
/// UniformDataItems in the tree and serialize their heavy datasets.
class SerializeDataOperation : public ItemVisitor {
public:
  /// Initialize using the given mode for Dataset access.
  /// @param mode Read, Create, or Modify Datasets during serialization.
  SerializeDataOperation( const Dataset::InitializeMode& mode = Dataset::kCreate );
  virtual ~SerializeDataOperation();

  /// Serialize a UniformDataItem's array into its dataset.
  virtual void apply( UniformDataItem& udi );

private:
  Dataset::InitializeMode mMode;
};

} // namespace xdm

#endif // xdm_SerializeDataOperation_hpp

