#include "../src/parsetreelogger/parsetreelogger.h"

int main(){

    ParseTreeLogger parseTreeLogger("foo.cpp");
    parseTreeLogger.logEntry("bar");
    parseTreeLogger.logEntry("baz");
    parseTreeLogger.logExit("baz");
    parseTreeLogger.logExit("bar");

}
