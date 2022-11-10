#include "PlayerInRangeDecision.h"

#include "Character.h"
#include "VMath.h"

using namespace MATH;


bool PlayerInRangeDecision::testValue()
{
	//distance to player is less than some value
	float thresholdDistance = 3.0f;
	
	//how to get player position????

	if (VMath::distance(owner->getPlayerPos(), owner->getPos()) < thresholdDistance)
	{
		std::cout << "in range" << std::endl;
		return true;
	}

	std::cout << "out of range" << std::endl;
	return false;
}
