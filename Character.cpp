#include "Character.h"

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;

	// Configure and instantiate the body to use for the demo
	if (!body)
	{
		float radius = 0.2;
		float orientation = 0.0f;
		float rotation = 0.0f;
		float angular = 0.0f;
		float maxSpeed = 4.0f;
		float maxAcceleration = 10.0f;
		float maxRotation = 2.0f;
		float maxAngular = 10.0f;
		body = new KinematicBody(
			Vec3(10.0f, 5.0f, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), 1.0f,
			radius,
			orientation,
			rotation,
			angular,
			maxSpeed,
			maxAcceleration,
			maxRotation,
			maxAngular
		);
	}

	if (!body)
	{
		return false;
	}

	return true;
}

bool Character::readStateMachineXML(string filename)
{
	stateMachine = new StateMachine(this);

	State* seekPlayer = new State(STATE::SEEK);
	State* doNothing = new State(STATE::DO_NOTHING);

	Condition* ifInRange = new ConditionInRange(this);

	doNothing->addTransition(
		new Transition(ifInRange, seekPlayer)
	);

	Condition* ifOutOfRange = new ConditionOutOfRange(this);

	seekPlayer->addTransition(
		new Transition(ifOutOfRange, doNothing)
	);

	stateMachine->setInitialState(doNothing);

	return true;
}

bool Character::readDecisionTreeXML(string filename)
{
	// let's pretend the XML parsing produced these instances

	if (filename == "playerinrange.xml")
	{
		DecisionTreeNode* falseNode = new Action(ACTION_SET::DO_NOTHING);
		DecisionTreeNode* trueNode = new Action(ACTION_SET::SEEK);

		decider = new PlayerInRangeDecision(this, trueNode, falseNode);
	}
	return true;
}

void Character::Update(float deltaTime)
{
	// create a new overall steering output
	SteeringOutput* steering;
	steering = new SteeringOutput();

	// calculate and set values in the overall steering output
	if (decider)
	{
		DecisionTreeNode* action = decider->makeDecision();
		Action* a = dynamic_cast<Action*>(action);
		switch (a->getValue()) {
		case ACTION_SET::SEEK:
			steerToSeekPlayer(steering);
			break;
		case ACTION_SET::DO_NOTHING:
			break;
		}
	}
	if (stateMachine)
	{
		stateMachine->update();
		switch (stateMachine->getCurrentStateName())
		{
		case STATE::SEEK:
			steerToSeekPlayer(steering);
			break;
		case STATE::DO_NOTHING:
			break;
		}
	}

	// apply the steering to the equations of motion
	body->Update(deltaTime, steering);

	// clean up memory
	// (delete only those objects created in this function)
	if (steering)
	{
		delete steering;
	}

}

void Character::steerToSeekPlayer(SteeringOutput* steering)
{
	vector<SteeringOutput*> steering_outputs;

	// set the target for steering.
	// (often the target is the Player)

	PlayerBody* target = scene->game->getPlayer();

	SteeringBehaviour* steering_algorithm = new Seek(body, target);
	steering_outputs.push_back( steering_algorithm->getSteering() );

	// Add together any steering outputs
	for (unsigned i = 0; i < steering_outputs.size(); i++)
	{
		if (steering_outputs[i])
		{
			*steering += *steering_outputs[i];
		}
	}

	// clean up memory
	if (steering_algorithm)
	{
		delete steering_algorithm;
	}
}

void Character::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void Character::render(float scale)
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int    w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(body->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * body->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees.
	float orientation = body->getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, body->getTexture(), nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);
}
