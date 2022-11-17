#include "ConditionInRange.h"
#include "VMath.h"

using namespace MATH;

#include "Character.h"

bool ConditionInRange::test()
{
	float thresholdDistance = 2.0f;
	if (VMath::distance(owner->getPlayerPos(), owner->getPos()) < thresholdDistance )
	{
		return true;
	}
	return false;
}