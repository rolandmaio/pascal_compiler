#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ParseTreeLoggerExceptionTest
#include<boost/test/unit_test.hpp>
#include "../src/parsetreelogger/parsetreeloggerexception.h"

BOOST_AUTO_TEST_CASE(what_test){
    ParseTreeLoggerException envVarException(PARSE_TREE_LOG_DIR_ENV_VAR_ERROR);
    BOOST_CHECK_EQUAL(envVarException.what(), "Fatal error: Env var PASCAL_COMPILER_PARSETREELOGGER_DIR is not set.");
    ParseTreeLoggerException openFileException(OPEN_FILE_ERROR, "Lorem Ipsum Dolor Set!");
    BOOST_CHECK_EQUAL(openFileException.what(), "There was an error opening the file. Lorem Ipsum Dolor Set!");
    ParseTreeLoggerException badCloseTagException(CLOSE_ON_UNOPENED_TAG_ERROR, "foo");
    BOOST_CHECK_EQUAL(badCloseTagException.what(), "printClosingTag called on tag: foo which was never opened.");
    ParseTreeLoggerException catchAllException(-1);
    BOOST_CHECK_EQUAL(catchAllException.what(), "There was an error associated with the ParseTreeLogger.");
}
