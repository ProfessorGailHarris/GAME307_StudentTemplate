#include "StaticBody.h"


void StaticBody::Update(
	float deltaTime, KinematicSteeringOutput* steering
)
{
	//update using the base class
	Body::Update(deltaTime);
	newOrientation();

	// then... deal with steering

	vel = steering->velocity;
	rotation = steering->rotation;

	// Clip to max speed
	if (VMath::mag(vel) > maxSpeed)
	{
		vel = VMath::normalize(vel) * maxSpeed;
	}

	// Clip to max rotation
	if (rotation > maxRotation)
	{
		rotation = maxRotation;
	}
}

void StaticBody::newOrientation()
{
	if (VMath::mag(vel) > 0.0f)
	{
		orientation = atan2(-vel.y, vel.x);

	}
}
