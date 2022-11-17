#ifndef CONDITION_OUT_OF_RANGE_H
#define CONDITION_OUT_OF_RANGE_H

#include "Condition.h"

class ConditionOutOfRange :
    public Condition
{
private:

public:
    ConditionOutOfRange(Character* owner_)
        : Condition{ owner_ }
    {}

    bool test();
};

#endif
