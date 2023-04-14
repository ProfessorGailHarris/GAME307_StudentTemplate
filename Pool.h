#ifndef POOL_H
#define POOL_H

// Inspired by https://gameprogrammingpatterns.com/object-pool.html

#include "MMath.h"
#include "Particle.h"

using namespace MATH;

class Pool
{
private:
	static const int POOL_SIZE = 5;
	Particle objects[POOL_SIZE];
	Particle* head;
	GameManager* game;

public:
	Pool();
	bool OnCreate(GameManager* game_);
	void createParticle(Vec3 pos, Vec3 vel, int lifetime, float orientation = 0.0f);
	void update(float deltaTime);
	void render(GameManager* game);
	
};

#endif
