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
#define BOOST_TEST_MODULE ImplTreeBuilder
#include <boost/test/unit_test.hpp>

#include <xdmf/impl/TreeBuilder.hpp>

#include <xdm/AllDataSelection.hpp>
#include <xdm/DataSelectionMap.hpp>
#include <xdm/Dataset.hpp>
#include <xdm/TypedStructuredArray.hpp>
#include <xdm/VectorStructuredArray.hpp>
#include <xdm/UniformDataItem.hpp>

#include <xdmHdf/HdfDataset.hpp>

#include <libxml/parser.h>
#include <libxml/tree.h>

namespace {

char const * const kTestDatasetFilename = "BuildTreeTest.h5";

// Create a simple test HDF5 file.
void createHdfFile() {
  xdm::RefPtr< xdmHdf::HdfDataset > dataset( new xdmHdf::HdfDataset );
  dataset->setFile( kTestDatasetFilename );
  xdmHdf::GroupPath path;
  path.push_back( "group1" );
  path.push_back( "group2" );
  dataset->setGroupPath( path );
  dataset->setDataset( "dataset" );
  xdm::RefPtr< xdm::VectorStructuredArray< double > > array(
    new xdm::VectorStructuredArray< double >( 9 ) );
  for ( int i = 1; i <= 9; i++ ) {
    (*array)[i-1] = i;
  }

  // write the array
  dataset->initialize(
    xdm::primitiveType::kDouble,
    xdm::makeShape( 3, 3),
    xdm::Dataset::kCreate );
  dataset->serialize( array.get(), xdm::DataSelectionMap() );
  dataset->finalize();
}

BOOST_AUTO_TEST_CASE( buildUniformDataItem ) {
  char const * const kXml =
  "<DataItem Name='test' "
  "  ItemType='Uniform'"
  "  Dimensions='3 3'"
  "  NumberType='Float'"
  "  Precision='8'"
  "  Format='HDF'>"
  "  BuildTreeTest.h5:/group1/group2/dataset"
  "</DataItem>";
  double resultData[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

  createHdfFile();

  xmlDocPtr document = xmlParseDoc( reinterpret_cast< const xmlChar *>(kXml) );
  xmlNode * rootNode = xmlDocGetRootElement( document );

  xdmf::impl::TreeBuilder builder( document );
  xdm::RefPtr< xdm::UniformDataItem > item 
    = builder.buildUniformDataItem( rootNode );
  BOOST_REQUIRE( item );

  BOOST_CHECK_EQUAL( item->dataType(), xdm::primitiveType::kDouble );
  BOOST_CHECK_EQUAL( item->dataspace(), xdm::makeShape( 3, 3 ) );
  BOOST_REQUIRE( item->dataset() );
  BOOST_CHECK_EQUAL( item->dataset()->format(), "HDF" );

  xdm::RefPtr< xdmHdf::HdfDataset > dataset
    = xdm::dynamic_pointer_cast< xdmHdf::HdfDataset >( item->dataset() );
  BOOST_REQUIRE( dataset );

  BOOST_CHECK_EQUAL( dataset->file(), kTestDatasetFilename );
  xdmHdf::GroupPath path;
  path.push_back( "group1" );
  path.push_back( "group2" );
  BOOST_CHECK_EQUAL_COLLECTIONS(
    dataset->groupPath().begin(), dataset->groupPath().end(),
    path.begin(), path.end() );
  BOOST_CHECK_EQUAL( "dataset", dataset->dataset() );

  // check the data
  item->initializeDataset( xdm::Dataset::kRead );
  item->deserializeData();
  item->finalizeDataset();

  xdm::RefPtr< xdm::TypedStructuredArray< double > > array
    = item->typedArray< double >();
  BOOST_REQUIRE( array );
  BOOST_CHECK_EQUAL_COLLECTIONS(
    array->begin(), array->end(),
    resultData, resultData + 9 );

  xmlFreeDoc( document );
}

} // namespace
