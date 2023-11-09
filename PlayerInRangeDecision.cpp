#include "PlayerInRangeDecision.h"

using namespace MATH;

#include "Character.h"

bool PlayerInRangeDecision::testValue()
{
	if (VMath::distance(owner->getPlayerPos(), owner->getPos()) < 2.0f)
	{
		return true;
	}
	return false;
}
