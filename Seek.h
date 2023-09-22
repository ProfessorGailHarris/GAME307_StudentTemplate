#ifndef SEEK_H
#define SEEK_H


#include "SteeringBehaviour.h"
class Seek :
    public SteeringBehaviour
{
protected:
    Body* target;

public:
    Seek(Body* npc_, Body* target_);
    virtual ~Seek();
    SteeringOutput* getSteering();
};

#endif
