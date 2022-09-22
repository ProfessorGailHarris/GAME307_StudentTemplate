#include "Seek.h"

Seek::Seek(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
}

Seek::~Seek()
{

}

SteeringOutput* Seek::getSteering()
{
	// Get direction to target
	result->linear = target->getPos() - character->getPos();

	// accelerate along this direction
	result->linear = VMath::normalize(result->linear) * character->getMaxAcceleration();

	result->angular = 0.0f;

	return result;
}