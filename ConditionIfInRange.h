#pragma once
#include "Condition.h"
#include "VMath.h"

using namespace MATH;

class ConditionIfInRange :
    public Condition
{
public:
    ConditionIfInRange(Character* owner_)
        : Condition{ owner_ }
    {
    // any other initializations
    }

    bool test();
};

class ConditionIfOutOfRange :
    public Condition
{
public:
    ConditionIfOutOfRange(Character* owner_)
        : Condition{ owner_ }
    {
        // any other initializations
    }

    bool test();
};

