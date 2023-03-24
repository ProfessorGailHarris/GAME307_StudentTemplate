#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "KinematicBody.h"
#include "Seek.h"
#include "Action.h"
#include "Decision.h"
#include "PlayerInRangeDecision.h"
#include "StateMachine.h"
#include "ConditionIfInRange.h"

using namespace std;

class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;

	void steerToSeekPlayer(SteeringOutput* steering);

	DecisionTreeNode* decider;
	StateMachine* stateMachine;

public:
	Character()
	{
		body = NULL;
		scene = NULL;
		stateMachine = NULL;
		decider = NULL;
	};

	~Character()
	{
		if (body) delete body;
	};

	bool OnCreate(Scene* scene_);
	void OnDestroy() {};
	bool setTextureWith(string file);
	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f);
	bool readDecisionTreeXML(string filename);
	bool readStateMachineXML(string filename);

	Vec3 getPos();
	Vec3 getPlayerPos();

};

#endif

