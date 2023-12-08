#include "Condition.h"
#include "SafeCharacter.h" // include here, not in .h file, to avoid circular reference

using namespace MATH;

bool ConditionOutOfRange::test()
{
    // should only be able to call methods from owner that do not change internals of the NPC
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
