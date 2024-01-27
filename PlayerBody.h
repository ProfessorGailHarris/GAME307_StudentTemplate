//
//  PlayerBody.h
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include <stdio.h>
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
        texture = NULL;
    }

    PlayerBody(
        Vec3 pos_, Vec3 vel_, Vec3 accel_,
        float mass_,
        float radius_,
        float orientation_,
        float rotation_,
        float angular_,
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
        , angular_
        , maxSpeed_
        , maxAcceleration_
        , maxRotation_
        , maxAngular_
    }
        , game{ game_ }
    {}
    
    // use the base class versions of getters

    bool OnCreate();
    void OnDestroy();
    void Render( float scale = 1.0f ) const;
    void HandleEvents( const SDL_Event& event );
    void Update( float deltaTime );
    void resetToOrigin();
    void setImage(SDL_Surface* image_)
    {
        if (image) SDL_FreeSurface(image);
        image = image_; 
    }
    void setTexture( SDL_Texture* texture_ )
    {
        if (texture) SDL_DestroyTexture(texture);
        texture = texture_; 
    }
    
};

#endif /* PLAYERBODY_H */
