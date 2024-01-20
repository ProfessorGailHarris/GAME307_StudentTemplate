#ifndef KINEMATIC_SEEK_H
#define KINEMATIC_SEEK_H

#include <Vector.h>
#include <VMath.h>
#include "Body.h"
#include "KinematicSteeringOutput.h"

using namespace MATH;

class KinematicSeek
{
private:
	KinematicSteeringOutput* result;
	const Body* character;
	const Body* target;

public:
	KinematicSeek(const Body* character_, const Body* target_);
	virtual ~KinematicSeek();

	KinematicSteeringOutput* getSteering();
};

#endif
