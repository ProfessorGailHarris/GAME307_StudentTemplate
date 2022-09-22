#ifndef STEERING_BEHAVIOUR_H
#define STEERING_BEHAVIOUR_H

#include "VMath.h"
#include "KinematicBody.h"
#include "SteeringOutput.h"

// Abstract class
// Steering behaviour subclasses will inherit from here and
// must implement the getSteering() function.

class SteeringBehaviour
{
protected:
	SteeringOutput* result;
	Body* character;

public:
	SteeringBehaviour();
	virtual SteeringOutput* getSteering() = 0;
	virtual ~SteeringBehaviour()
	{
		if (result)
		{
			delete result;
		}
	}

};

#endif
