#include "StaticBody.h"

void StaticBody::Update(float deltaTime, KinematicSteeringOutput* steering)
{
	// can do this at beginning or end
	Body::Update(deltaTime);

	// set the value based on the steering input
	if (steering == nullptr)
	{
		vel = Vec3();
		orientation = 0.0f;
		return;
	}

	vel = steering->velocity;
	rotation = steering->rotation;

	//clip to max
	if (VMath::mag(vel) > maxSpeed)
		vel = VMath::normalize(vel) * maxSpeed;

	rotation = rotation > maxRotation ? maxRotation : rotation;

}

void StaticBody::newOrientation()
{
	if (VMath::mag(vel) > 0.0f)
	{
		orientation = atan2(-vel.y, vel.x);
	}
}
