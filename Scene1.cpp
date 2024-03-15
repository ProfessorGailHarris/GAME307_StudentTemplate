#include "Scene1.h"

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// create a NPC
	blinky = nullptr;

	myNPC = nullptr;
}

Scene1::~Scene1(){}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// Set up myNPC kinematic character
	Vec3 position = Vec3(5.0f, 3.0f, 0.0f);
	float orientation = 0.0f;
	float maxSpeed = 1.0f;
	float maxRotation = 1.0f;
	myNPC = new StaticBody(
		position,
		orientation,
		maxSpeed,
		maxRotation
	);
	image = IMG_Load("Clyde.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	//error checking
	if (image == nullptr)
	{
		std::cerr << "Can't open clyde image\n";
		return false;
	}
	else if (texture == nullptr)
	{
		std::cerr << "Can't open clyde texture\n";
		return false;
	}
	else
	{
		myNPC->setTexture(texture);
		SDL_FreeSurface(image);
	}

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setTextureWith("Blinky.png") )
	{
		return false;
	}

	if (!blinky->readDecisionTreeFromFile("seekIfInRange"))
	{
		return false;
	}

	// end of character set ups

	return true;
}

void Scene1::OnDestroy() 
{
	if (myNPC->getTexture())
		SDL_DestroyTexture(myNPC->getTexture());
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}
}

void Scene1::Update(const float deltaTime) {

	KinematicSteeringOutput* steering;

	// create seek algorithm
	KinematicSeek* steeringAlgorithm;
	steeringAlgorithm = new KinematicSeek(myNPC, game->getPlayer());
	steering = steeringAlgorithm->getSteering();

	myNPC->Update(deltaTime, steering);

	// Calculate and apply any steering for npc's
	blinky->Update(deltaTime);

	// Update player
	game->getPlayer()->Update(deltaTime);

	// Clean up memory
	if (steeringAlgorithm) delete steeringAlgorithm;
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//render myNPC (please do better OO code than this)
	SDL_Rect rect;
	Vec3 screenCoords;
	int w, h;

	//convert form game coords to screen coords
	screenCoords = projectionMatrix * myNPC->getPos();
	float scale = 0.15f;
	SDL_QueryTexture(myNPC->getTexture(), nullptr, nullptr, &w, &h);
	
	rect.w = static_cast<int>(w * scale);
	rect.h = static_cast<int>(h * scale);
	rect.x = static_cast<int>(screenCoords.x - 0.5 * rect.w);
	rect.y = static_cast<int>(screenCoords.y - 0.5 * rect.h);

	float orientation = myNPC->getOrientation();
	float degrees = orientation * 180.0f / M_PI;

	//SDL_RenderCopyEx(renderer, myNPC->getTexture(), nullptr, &rect, degrees, nullptr, SDL_FLIP_NONE);

	// render any npc's
	blinky->render(0.15f);

	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
