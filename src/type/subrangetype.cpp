#ifndef SUBRANGETYPE_IMPL
#define SUBRANGETYPE_IMPL

#include "subrangetype.h"

SubrangeType::SubrangeType(Type index_type, int low, int high){
    this->index_type = index_type;
    this->int_low = low;
    this->int_high = high;
}

#endif
