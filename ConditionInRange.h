#ifndef CONDITION_IN_RANGE_H
#define CONDITION_IN_RANGE_H

#include "Condition.h"

class ConditionInRange :
    public Condition
{
private:

public:
    ConditionInRange(Character* owner_)
        : Condition{ owner_ }
    {
    // put other stuff here if needed in constructor
    }

    bool test();

};

#endif
