#ifndef STACK_ELEMENT
#define STACK_ELEMENT

#include<cstdlib>
using std::size_t;

union StackElement {
    bool boolean;
    char character,
         *string_ptr;
    int integer;
    float real;
    size_t address;
};

#endif
