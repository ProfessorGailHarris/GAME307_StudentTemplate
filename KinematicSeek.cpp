#include "KinematicSeek.h"

KinematicSeek::KinematicSeek(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new KinematicSteeringOutput();
}

KinematicSeek::~KinematicSeek()
{
	if (result) { delete result;  }
}

KinematicSteeringOutput* KinematicSeek::getSteering()
{
	result->velocity = target->getPos() - character->getPos();

	//go full speed along this direction
	result->velocity = VMath::normalize(result->velocity);
	result->velocity = character->getMaxSpeed() * result->velocity;

	result->rotation = 0.0f;
	return result;
}