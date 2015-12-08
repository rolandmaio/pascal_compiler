#ifndef SUBRANGETYPE
#define SUBRANGETYPE

#include "type.h"

class SubrangeType : public Type {

    public:
        SubrangeType(Type index_type, int low, int high);

    private:
        Type index_type;
        int int_low,
            int_high;

};

#endif
