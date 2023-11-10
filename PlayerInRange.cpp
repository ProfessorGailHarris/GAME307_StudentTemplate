#include "PlayerInRange.h"
#include "Character.h"

bool PlayerInRange::testValue()
{
	//Test if the player is in range
	//get player position
	//get this npc's position

	if (VMath::distance(owner->getPos(), owner->getPlayerPos()) < 2.0f)
	{
		return true;
	}
	return false;
}

