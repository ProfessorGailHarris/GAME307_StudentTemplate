#include "ConditionIfInRange.h"
#include "Character.h"

bool ConditionIfInRange::test()
{
	float thresholdDistance = 2.0f;
	if (VMath::distance(owner->getPlayerPos(), owner->getPos()) < thresholdDistance)
	{
		return true;
	}
	return false;
}

bool ConditionIfOutOfRange::test()
{
	float thresholdDistance = 3.5f;
	if (VMath::distance(owner->getPlayerPos(), owner->getPos()) > thresholdDistance)
	{
		return true;
	}
	return false;
}
