#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "KinematicBody.h"
#include "Seek.h"

#include "Decision.h"		//which includes DecisionTreeNode.h
#include "PlayerInRangeDecision.h"
#include "Action.h"


class DecisionTreeNode;

#include "StateMachine.h"

using namespace std;

class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;

	DecisionTreeNode* decider;
	StateMachine* stateMachine;

public:
	Character()
	{
		body = NULL;
		scene = NULL;
		decider = NULL;
		stateMachine = NULL;
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
	void steerToSeekPlayer(SteeringOutput* steering);

	Vec3 getPos() { return body->getPos(); }
	Vec3 getPlayerPos() { return scene->game->getPlayer()->getPos(); }

	bool readDecisionTreeXML(string filename);
	bool readStateMachineXML(string filename);
};

#endif

