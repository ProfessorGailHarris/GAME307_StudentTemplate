#include "StaticBody.h"

void StaticBody::Update(float deltaTime, KinematicSteeringOutput* steering_)
{
	// can do this at beginning or end
	Body::Update(deltaTime);
	newOrientation();

	// set the values based on the steering input
	if (steering_ == NULL)
	{
		vel = Vec3();
		rotation = 0.0f;
		return;
	}

	vel = steering_->velocity;
	rotation = steering_->rotation;

	// clip to max
	if (VMath::mag(vel) > maxSpeed)
		vel = VMath::normalize(vel) * maxSpeed;

	rotation = (rotation > maxRotation ? maxRotation : rotation);
}

void StaticBody::newOrientation()
{
	if (VMath::mag(vel) > FLT_EPSILON)
	{
		orientation = atan2(-vel.y, vel.x);
	}
}
