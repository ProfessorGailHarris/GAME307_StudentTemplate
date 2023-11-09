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

bool Character::setTextureWith(string file)
{
	SDL_Surface* image = IMG_Load(file.c_str());
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture) 
	{
		std::cerr << "Can't create texture" << std::endl;
		return false;
	}
	body->setTexture(texture);
	return true;
}


void Character::Update(float deltaTime)
{
	// create a new overall steering output
	SteeringOutput* steering = new SteeringOutput();

	DecisionTreeNode* action = decisionTree->makeDecision();
	// need static cast to get the value of the action
	Action* a = static_cast<Action*>(action);

	switch (a->getValue())
	{
	case ACTION_SET::SEEK:
		steerToSeekPlayer(steering);
		break;

	case ACTION_SET::DO_NOTHING:
		break;

	default:
		break;
	}

	//steerToSeekPlayer(steering);
	//steerToFleePlayer(steering);
	//steerToPursuePlayer(steering);

	body->Update(deltaTime, steering);

	// clean up memory
	// (delete only those objects created in this function)
	if (steering)
	{
		delete steering;
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

void Character::steerToSeekPlayer(SteeringOutput* steering)
{
	std::vector<SteeringOutput*> steering_outputs;

	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	PlayerBody* target = scene->game->getPlayer();

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algorithm = new Seek(body, target);
	steering_outputs.push_back(steering_algorithm->getSteering());

	// add another behaviour ...
	// create the algorithm instance
	// push getSteering() onto our list

	//add together steering outputs
	for (int i = 0; i < steering_outputs.size(); i++)
	{
		if (steering_outputs[i])
		{
			*steering += *steering_outputs[i];
		}
	}

	if (steering_algorithm)
	{
		delete steering_algorithm;
	}
}

void Character::steerToFleePlayer(SteeringOutput* steering)
{
	std::vector<SteeringOutput*> steering_outputs;

	// set the target for steering
	PlayerBody* target = scene->game->getPlayer();

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algorithm = new Flee(body, target);
	steering_outputs.push_back(steering_algorithm->getSteering());

	//add together steering outputs
	for (int i = 0; i < steering_outputs.size(); i++)
	{
		if (steering_outputs[i])
		{
			*steering += *steering_outputs[i];
		}
	}

	if (steering_algorithm)
	{
		delete steering_algorithm;
	}
}

bool Character::readDecisionTreeFromFile(string file)
{
	//Gail is faking it here, not actually reading a file
	if (file == "seek")
		decisionTree = new Action(ACTION_SET::SEEK);
	else if (file == "blinky")
	{
		DecisionTreeNode* trueNode = new Action(ACTION_SET::SEEK);
		DecisionTreeNode* falseNode = new Action(ACTION_SET::DO_NOTHING);
		decisionTree = new PlayerInRangeDecision(trueNode, falseNode, this);
	}
	else
		return false;

	return true;
}
