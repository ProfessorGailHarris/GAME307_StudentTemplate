#include "StaticBody.h"

void StaticBody::Update(
	float deltaTime, KinematicSteeringOutput* steering
)
{
	// can do this call at end or at beginning
	Body::Update(deltaTime);
	newOrientation();

	if (steering == NULL)
	{
		return;
	}
	//then ... deal with steering
	vel = steering->velocity;
	rotation = steering->rotation;

	// clip to max
	if (VMath::mag(vel) > maxSpeed)
	{
		vel = VMath::normalize(vel) * maxSpeed;
	}

	// clip to max rotation
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
