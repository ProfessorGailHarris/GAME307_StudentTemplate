#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "KinematicBody.h"
#include "Seek.h"

#include "Action.h"
#include "PlayerInRange.h"

using namespace std;

class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;

	DecisionTreeNode* decisionTree;

	void steerToSeekPlayer(SteeringOutput* steering);

public:
	Character()
	{
		body = NULL;
		scene = NULL;
		decisionTree = NULL;
	};

	~Character() {};

	bool OnCreate(Scene* scene_);
	void OnDestroy();
	bool setTextureWith(string file);
	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f);

	bool readDecisionTreeFromFile(string file);
	Vec3 getPos() const { return body->getPos(); }
	Vec3 getPlayerPos() const { return scene->game->getPlayer()->getPos(); }
};

#endif

