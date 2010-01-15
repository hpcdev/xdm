#define BOOST_TEST_MODULE 
#include <boost/test/unit_test.hpp>

#include <xdmGrid/StructuredTopology.hpp>

BOOST_AUTO_TEST_CASE( writeMetadata ) {
  xdmGrid::StructuredTopology t;
  xdm::XmlMetadataWrapper xml( new xdm::XmlObject );

  xdm::DataShape<> shape(3);
  shape[0] = 1;
  shape[1] = 2;
  shape[2] = 3;
  t.setShape( shape );

  t.writeMetadata( xml );

  BOOST_CHECK_EQUAL( "Topology", xml.tag() );
  BOOST_CHECK_EQUAL( "1 2 3", xml.attribute( "Dimensions" ) );
}

int main( int argc, char* argv[] ) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

