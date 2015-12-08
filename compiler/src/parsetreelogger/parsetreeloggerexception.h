#ifndef PARSETREELOGGEREXCEPTION
#define PARSETREELOGGEREXCEPTION

#include<stdexcept>
#include<string>

#define OPEN_FILE_ERROR 0
#define PARSE_TREE_LOG_DIR_ENV_VAR_ERROR 1
#define CLOSE_ON_UNOPENED_TAG_ERROR 2

class ParseTreeLoggerException : std::logic_error {

    public:
        ParseTreeLoggerException(int errorCode) : std::logic_error(""), errorCode(errorCode) {}
        ParseTreeLoggerException(int errorCode, std::string message) : std::logic_error(message), errorCode(errorCode), message(message) {}
        virtual const char* what() const noexcept;

    private:
        std::string message;
        int errorCode;

};

const char* ParseTreeLoggerException::what() const noexcept {
    std::string result = "";
    switch(this->errorCode){
        case OPEN_FILE_ERROR:
            result = "There was an error opening the file. " + this->message;
            break;
        case PARSE_TREE_LOG_DIR_ENV_VAR_ERROR:
            return "Fatal error: Env var PASCAL_COMPILER_PARSETREELOGGER_DIR is not set.";
            break;
        case CLOSE_ON_UNOPENED_TAG_ERROR:
            result = "printClosingTag called on tag: " + this->message + " which was never opened.";
            break;
        default:
            result = "There was an error associated with the ParseTreeLogger.";
    }
    return result.c_str();
}

#endif
