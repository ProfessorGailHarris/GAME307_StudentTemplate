#include "Condition.h"
#include "Character.h" // include here, not in .h file, to avoid circular reference

using namespace MATH;

bool ConditionOutOfRange::test()
{
    float threshold = 2.0f;
    if (VMath::distance(owner->getPlayerPos(), owner->getPos()) > threshold)
    {
        return true;
    }
    return false;
}

bool ConditionIfInRange::test()
{
    float threshold = 2.0f;
    if (VMath::distance(owner->getPlayerPos(), owner->getPos()) < threshold)
    {
        return true;
    }
    return false;
}