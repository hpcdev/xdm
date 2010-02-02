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
#ifndef xdmGrid_UnstructuredTopology_hpp
#define xdmGrid_UnstructuredTopology_hpp

#include <xdmGrid/Topology.hpp>
#include <xdmGrid/UnstructuredTopologyConventions.hpp>

#include <xdm/DataShape.hpp>

#include <xdmGrid/NamespaceMacro.hpp>

XDM_GRID_NAMESPACE_BEGIN

class Element;
class ElementImpl;

/// Base class for all unstructured topologies. If the connectivity is different
/// from the standard, an order may be specified.
class UnstructuredTopology : public Topology {
public:
  UnstructuredTopology();
  virtual ~UnstructuredTopology();

  XDM_META_ITEM( UnstructuredTopology );

  /// Set the number of elements in the topology.
  void setNumberOfElements( std::size_t numberOfElements );
  /// Get the number of elements in the topology.
  std::size_t numberOfElements() const;

  /// Define how many nodes make up a single element.
  void setNodesPerElement( std::size_t nodesPerElement );
  /// Determine how many nodes make up a single element.
  std::size_t nodesPerElement() const;

  /// Set the shape of the elements.
  void setElementShape( const ElementShape::Type& shape );
  /// Get the shape of the elements.
  ElementShape::Type elementShape() const;

  /// Set the node ordering convention for the shape of the elements. For example,
  /// Exodus II orders the nodes of a linear tetrahedron differently than some
  /// other formats.
  void setNodeOrdering( const NodeOrderingConvention::Type& order );
  /// Get the node odering for the shape of these elements.
  NodeOrderingConvention::Type nodeOrdering() const;

  /// Get an element by index.
  Element element( std::size_t elementIndex );
  /// Get a const element by index.
  const Element element( std::size_t elementIndex ) const;

  /// Set the connectivity values to the input DataItem. If the connectivity
  /// is not specified, then there is a default connectivity determined by the
  /// topology type.
  void setConnectivity( xdm::DataItem* connectivity );

  virtual void traverse( xdm::ItemVisitor& iv );

  virtual void writeMetadata( xdm::XmlMetadataWrapper& xml );

private:
  xdm::RefPtr< xdm::DataItem > mConnectivity;
  xdm::RefPtr< ElementImpl > mElementSharedImpl;
  std::size_t mNumberOfElements;
  std::size_t mNodesPerElement;
  NodeOrderingConvention::Type mOrdering;
  ElementShape::Type mShape;
};

XDM_GRID_NAMESPACE_END

#endif // xdmGrid_UnstructuredTopology_hpp

