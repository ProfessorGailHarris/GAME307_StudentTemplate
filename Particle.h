#ifndef PARTICLE_H
#define PARTICLE_H

// inspired by https ://gameprogrammingpatterns.com/object-pool.html

#include "MMath.h"
#include <SDL.h>
#include <SDL_image.h>

class GameManager;

using namespace MATH;

class Particle
{
private:
	int framesLeft;
	SDL_Surface* image;
	SDL_Texture* texture;

	union
	{
		// state when it's in use
		struct
		{
			Vec3 pos;
			Vec3 vel;
			float orientation = 0.0f;
		} live;

		// state when it's available (not in use)
		Particle* next = NULL;
	};

public:
	Particle() : framesLeft(0)
	{}

	bool OnCreate(SDL_Renderer* renderer);

	void init(Vec3 pos_, Vec3 vel_, int lifetime_, float orientation_ = 0.0f)
	{
		framesLeft = lifetime_;
		live.pos = pos_;
		live.vel = vel_;
		live.orientation = orientation_;
	}

	bool Update(float deltaTime);

	void Render(GameManager* game);

	bool inUse() const { return framesLeft > 0; }

	Particle* getNext() { return next; }

	void setNext(Particle* next_) { next = next_; }
	
};

#endif
