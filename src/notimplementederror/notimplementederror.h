#ifndef NOTIMPLEMENTEDERROR
#define NOTIMPLEMENTEDERROR

#include<stdexcept>
#include<string>

class NotImplementedError : std::logic_error{

    public:
        NotImplementedError(std::string function) : std::logic_error(function), function(function){}
        virtual const char* what() const noexcept;
    private:
        std::string function;

};

const char* NotImplementedError::what() const noexcept{
    std::string result = function + " is not yet implemented.";
    return result.c_str();
}

#endif
