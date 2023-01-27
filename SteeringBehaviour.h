#ifndef STEERING_BEHAVIOUR_H
#define STEERING_BEHAVIOUR_H

#include "VMath.h"
#include "KinematicBody.h"
#include "SteeringOutput.h"

// Abstract class
// Steering behaviour subclasses will inherit from here and
// must implement getSteering() function

class SteeringBehaviour
{
protected:
	SteeringOutput* result;
	Body* character;

public:
	SteeringBehaviour()
	{
		result = new SteeringOutput();
		character = NULL;
	}
	virtual ~SteeringBehaviour()
	{
		if (result)
		{
			delete result;
		}
	}
	// pure virtual function
	virtual SteeringOutput* getSteering() = 0;
};

#endif
