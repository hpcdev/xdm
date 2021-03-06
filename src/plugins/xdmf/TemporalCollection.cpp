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
#include <xdmf/TemporalCollection.hpp>

#include <xdmf/XdmfHelpers.hpp>

#include <xdm/CollectMetadataOperation.hpp>
#include <xdm/SerializeDataOperation.hpp>
#include <xdm/ReferencedObject.hpp>
#include <xdm/RefPtr.hpp>
#include <xdm/UpdateVisitor.hpp>
#include <xdm/XmlObject.hpp>

#include <xdmGrid/Domain.hpp>
#include <xdmGrid/CollectionGrid.hpp>

namespace xdmf {

namespace {

xdm::RefPtr< xdm::XmlObject > openTemporalCollection() 
{
  xdm::RefPtr< xdm::XmlObject > xdmf = createXdmfRoot();

  xdm::RefPtr< xdm::XmlObject > domain( new xdm::XmlObject( "Domain" ) );
  xdmf->appendChild( domain );

  xdm::RefPtr< xdm::XmlObject > grid( new xdm::XmlObject ( "Grid" ) );
  grid->appendAttribute( "GridType", "Collection" );
  grid->appendAttribute( "CollectionType", "Temporal" );
  domain->appendChild( grid );

  return xdmf;
}

} // namespace

TemporalCollection::TemporalCollection( 
  const std::string& metadataFile,
  xdm::Dataset::InitializeMode mode ) :
  TimeSeries( mode ),
  mFilename( metadataFile ),
  mFileStream(),
  mXmlStream( mFileStream )
{
}

TemporalCollection::~TemporalCollection()
{
}

void TemporalCollection::open() 
{
  mFileStream.open( mFilename.c_str(), std::ios::out );
  mFileStream << "<?xml version='1.0'?>\n";
  xdm::RefPtr< xdm::XmlObject > xdmf = openTemporalCollection();
  mXmlStream.openContext( xdmf );
}

void TemporalCollection::updateGrid( xdm::RefPtr< xdmGrid::Grid > grid, std::size_t step ) {
  // update the data tree for a new timestep.
  xdm::UpdateVisitor update( step );
  grid->accept( update );
}

void TemporalCollection::writeGridMetadata( xdm::RefPtr< xdmGrid::Grid > grid ) {
  // write the metadata to the stream
  xdm::CollectMetadataOperation collect;
  grid->accept( collect );
  xdm::RefPtr< xdm::XmlObject > xml( collect.result() );
  mXmlStream.writeObject( xml );
}

void TemporalCollection::writeGridData( xdm::RefPtr< xdmGrid::Grid > grid ) {
  // serialize the heavy data
  xdm::SerializeDataOperation serializer( mode() );
  grid->accept( serializer );
}

void TemporalCollection::close()
{
  mXmlStream.closeStream();
}

} // namespace xdmf

