#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testtest
#include<boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(my_test_1)
{
    BOOST_CHECK(2 == 2);
}
