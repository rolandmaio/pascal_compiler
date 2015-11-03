#ifndef NOTIMPLEMENTEDERROR
#define NOTIMPLEMENTEDERROR

#include<stdexcept>
#include<string>

class NotImplementedError : std::logic_error{

    public:
        NotImplementedError(std::string function) : std::logic_error(function), function(function){}
        virtual const char* what() const noexcept { return std::logic_error::what(); };
    private:
        std::string function;

};

/*
virtual const char* what() const{
    function.append(" is not yet implemented.");
    return function.c_str();
}
*/

#endif
