#include "Pool.h"
#include "GameManager.h"

Pool::Pool()
{
	head = &objects[0];
	for (int i = 0; i < POOL_SIZE -1 ; i++)
	{
		objects[i].setNext(&objects[i + 1]);
	}
	objects[POOL_SIZE - 1].setNext(NULL);
}

bool Pool::OnCreate(GameManager* game_)
{
	game = game_;
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (!objects[i].OnCreate(game->getRenderer()))
		{
			return false;
		}
	}
	return true;
}

void Pool::createParticle(Vec3 pos, Vec3 vel, int lifetime, float orientation)
{
	// handle empty pool
	if (head == NULL) return;

	// remove first available particle
	Particle* newParticle = head;
	head = newParticle->getNext();

	newParticle->init(pos, vel, lifetime, orientation);
}

void Pool::update(float deltaTime)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (objects[i].Update(deltaTime))
		{
			//add this particle to the front of the stack
			objects[i].setNext(head);
			head = &objects[i];
		}
	}
}

void Pool::render(GameManager* game)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		objects[i].Render(game);
	}
}
