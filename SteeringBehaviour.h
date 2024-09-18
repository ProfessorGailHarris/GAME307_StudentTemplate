#ifndef STEERING_BEHAVIOUR_H
#define STEERING_BEHAVIOUR_H

#include <VMath.h>
#include "KinematicBody.h"
#include "SteeringOutput.h"

class SteeringBehaviour
{
protected:
	SteeringOutput* result;
	const Body* npc;

public:
	SteeringBehaviour()
	{
		result = new SteeringOutput();
		npc = NULL;
	}

	virtual ~SteeringBehaviour()
	{
		if (result)
		{
			delete result;
		}
	}

	virtual SteeringOutput* getSteering() = 0;
};

#endif
