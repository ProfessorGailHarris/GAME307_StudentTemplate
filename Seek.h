#ifndef SEEK_H
#define SEEK_H

#include "SteeringBehaviour.h"
class Seek :
    public SteeringBehaviour
{
protected:
    const Body* target;

public:
    Seek(const Body* npc_, const Body* target_);
    virtual ~Seek();
    SteeringOutput* getSteering();
};

#endif
