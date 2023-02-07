#ifndef STATIC_BODY_H
#define STATIC_BODY_H

// [TODO] define KinematicSteeringOutput, forward declare for now
//class KinematicSteeringOutput;
#include "KinematicSteeringOutput.h"

#include "Body.h"
class StaticBody :
    public Body
{
private:
    public:
    StaticBody() : Body{}
    {}

    StaticBody(
        Vec3 pos_,
        float orientation_,
        float maxSpeed_,
        float maxRotation_
    ) : Body{
        pos_,
        Vec3(),
        Vec3(),
        1.0f,
        1.0f,
        orientation_,
        0.0f,
        0.0f,
        maxSpeed_,
        0.0,
        maxRotation_,
        0.0f
    }
    {}

    void Update(float deltaTime, KinematicSteeringOutput* steering);
    void newOrientation();
};

#endif
