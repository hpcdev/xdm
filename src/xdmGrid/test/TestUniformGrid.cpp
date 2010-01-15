#define BOOST_TEST_MODULE 
#include <boost/test/unit_test.hpp>

#include <xdmGrid/UniformGrid.hpp>

BOOST_AUTO_TEST_CASE( writeMetadata ) {
  xdmGrid::UniformGrid g;

  xdm::RefPtr< xdm::XmlObject > obj( new xdm::XmlObject );
  xdm::XmlMetadataWrapper xml( obj );
  g.writeMetadata( xml );

  ASSERT_EQ( "Grid", xml.tag() );
  ASSERT_EQ( "Uniform", xml.attribute( "GridType" ) );
}

int main( int argc, char* argv[] ) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
