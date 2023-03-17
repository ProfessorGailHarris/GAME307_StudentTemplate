#include "PlayerInRangeDecision.h"

bool PlayerInRangeDecision::testValue()
{
    float thresholdDistance = 2.0f;

    if (VMath::distance(owner->getPlayerPos(), owner->getPos()) < thresholdDistance)
    {
        return true;
    }
    return false;
}
