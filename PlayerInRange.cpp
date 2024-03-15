#include "PlayerInRange.h"

using namespace MATH;

// avoid circular dependency
#include "Character.h"

bool PlayerInRange::testValue()
{
    if (VMath::distance(owner->getPlayerPos(), owner->getPos()) < 2.0f)
    {
        return true;
    }
    
    return false;
}
