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
#ifndef xdmGrid_StructuredTopology_hpp
#define xdmGrid_StructuredTopology_hpp

#include <xdmGrid/Topology.hpp>
#include <xdmGrid/UnstructuredTopologyConventions.hpp>

#include <xdm/DataShape.hpp>

#include <vector>

#include <xdmGrid/NamespaceMacro.hpp>

XDM_GRID_NAMESPACE_BEGIN

/// Grid topology for which connectivity is implicit.  Namely, node i is
/// connected to node i+1.  Examples of structured topologies are grid
/// topologies in two or three dimensions.
class StructuredTopology : public Topology {
public:
  StructuredTopology();
  virtual ~StructuredTopology();

  XDM_META_ITEM( StructuredTopology );

  /// Get the node odering for the shape of these elements. Always returns ExodusII because
  /// the elements are either quads or hexes.
  virtual NodeOrderingConvention::Type nodeOrdering() const;

  /// Set the shape defined by the elements in the topology.  This shape should
  /// correspond to the arrangement of elements in n-dimensional space.
  void setShape( const xdm::DataShape<>& shape );
  /// Get the shape defined by the Elements in the topology.
  const xdm::DataShape<>& shape() const;

  /// Get the type of a particular element. For structured meshes this always returns
  /// a quad or hex.
  virtual const ElementType::Type& elementType( std::size_t elementIndex ) const;

  virtual void writeMetadata( xdm::XmlMetadataWrapper& xml );

protected:
  virtual xdm::RefPtr< xdm::VectorRefImp< std::size_t > > createVectorImp();

private:
  std::vector< std::size_t > mNodes;
  xdm::DataShape<> mShape;
  ElementType::Type mElementType;
};

XDM_GRID_NAMESPACE_END

#endif // xdmGrid_StructuredTopology_hpp

