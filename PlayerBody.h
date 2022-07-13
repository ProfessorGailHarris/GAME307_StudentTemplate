//
//  PlayerBody.hpp
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef PlayerBody_hpp
#define PlayerBody_hpp

#include <stdio.h>
#include "VMath.h"
#include "Body.h"
#include "GameManager.h"

class PlayerBody : public Body
{
protected:
    class GameManager* game;

public:
    PlayerBody() : Body{}
    {
        game = nullptr;
    }

    PlayerBody(
        Vec3 pos_, Vec3 vel_, Vec3 accel_,
        float mass_,
        float radius_,
        float orientation_,
        float rotation_,
        float maxSpeed_,
        float maxAcceleration_,
        float maxRotation_,
        float maxAngular_,
        GameManager *game_
    ) : Body{
          pos_
        , vel_
        , accel_
        , mass_
        , radius_
        , orientation_
        , rotation_
        , maxSpeed_
        , maxAcceleration_
        , maxRotation_
        , maxAngular_
    }
        , game{ game_ }
    {}
    
    // use the base class versions of getters

    bool OnCreate();
    void Render( float scale = 1.0f );
    void HandleEvents( const SDL_Event& event );
    void Update( float deltaTime );
    void resetToOrigin();
    void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    
};

#endif /* PlayerBody_hpp */
