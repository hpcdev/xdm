#define BOOST_TEST_MODULE 
#include <boost/test/unit_test.hpp>

#include <xdm/ObjectCompositionMixin.hpp>

using xdm::ReferencedObject;
using xdm::ObjectCompositionMixin;
using xdm::RefPtr;

struct A : ReferencedObject {};
struct B : ReferencedObject {};

class TestHarness : 
  public ObjectCompositionMixin< A >,
  public ObjectCompositionMixin< B >
{};

class ObjectCompositionMixinTest : public ::testing::Test {
public:
	TestHarness t;
	A* a;
	B* b;
	ObjectCompositionMixinTest() :
		t(),
		a( new A ),
		b( new B ) {
		xdm::appendChild< A >( t, a );
		xdm::appendChild< B >( t, b );
	}
};

BOOST_AUTO_TEST_CASE( begin ) {
	ObjectCompositionMixin< A >::Iterator it = xdm::begin< A >( t );
	BOOST_CHECK_EQUAL( a, *it );
	ObjectCompositionMixin< B >::Iterator bit = xdm::begin< B >( t );
	BOOST_CHECK_EQUAL( b, *bit );
}

BOOST_AUTO_TEST_CASE( child ) {
	BOOST_CHECK_EQUAL( a, xdm::child< A >( t, 0 ) );
	BOOST_CHECK_EQUAL( b, xdm::child< B >( t, 0 ) );
}

int main( int argc, char* argv[] ) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

