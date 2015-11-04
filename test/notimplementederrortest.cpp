#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NotImplementedErrorTest
#include<boost/test/unit_test.hpp>
#include "../src/notimplementederror/notimplementederror.h"

BOOST_AUTO_TEST_CASE(what_test){
    NotImplementedError testError("function name");
    BOOST_CHECK_EQUAL(testError.what(), "function name is not yet implemented.");
}
