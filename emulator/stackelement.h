#ifndef STACK_ELEMENT
#define STACK_ELEMENT

#include<cstdlib>
using std::size_t;

union StackElement {
    bool boolean;
    char character,
         *string_ptr,
         *ret_ptr;
    int integer, int_address;
    float real;
    size_t address;
    StackElement *prev_bp;
};

#endif
