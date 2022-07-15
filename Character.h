#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "KinematicBody.h"

using namespace std;

class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;

public:
	Character()
	{
		body = NULL;
		scene = NULL;
	};
	// TODO add constructor that takes parameters for the body
	~Character() 
	{
		if (body) delete body;
	};
	bool OnCreate(Scene* scene_);
	void OnDestroy() {};
	
	void setTexture(SDL_Texture* texture_) 
	{
		body->setTexture(texture_); 
	}

	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f);

};

#endif

