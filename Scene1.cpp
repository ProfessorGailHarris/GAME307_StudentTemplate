#include "Scene1.h"
#include "KinematicSeek.h"


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

Scene1::~Scene1(){
	if (blinky) 
	{
		blinky->OnDestroy();
		delete blinky;
	}
}

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

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setTextureWith("Blinky.png") )
	{
		return false;
	}

	// set up myNPC
	Vec3 position = Vec3(5.0f, 3.5f, 0.0f);
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
		std::cerr << "Can't open clyde image" << std::endl;
		return false;
	}
	else if (texture == nullptr)
	{
		std::cerr << "Can't open clyde texture" << std::endl;
		return false;
	}
	else
	{
		myNPC->setTexture(texture);
		SDL_FreeSurface(image);
	}

	// end of character set ups

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	// Calculate and apply any steering for npc's
	//blinky->Update(deltaTime);

	KinematicSteeringOutput *steering = new KinematicSteeringOutput{ {1.0f,0.2f,0.0},0.0f };

	// create KinematicSeek
	KinematicSeek* steeringAlgorithm;
	Body* target;
	target = game->getPlayer();
	steeringAlgorithm = new KinematicSeek(myNPC, target);
	steering = steeringAlgorithm->getSteering();

	myNPC->Update(deltaTime, steering);

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	//blinky->render(0.15f);

	SDL_Rect rect;
	Vec3 screenCoords;
	int w, h;

	// convert from game coords to screen coords
	screenCoords = projectionMatrix * myNPC->getPos();
	float scale = 0.15f;
	SDL_QueryTexture(myNPC->getTexture(), nullptr, nullptr, &w, &h);

	rect.w = static_cast<int>(w * scale);
	rect.h = static_cast<int>(h * scale);
	rect.x = static_cast<int>(screenCoords.x - 0.5f * rect.w);
	rect.y = static_cast<int>(screenCoords.y - 0.5f * rect.h);

	float orientation = myNPC->getOrientation();
	float orientationDegrees = orientation * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, myNPC->getTexture(), nullptr, &rect,
		orientationDegrees, nullptr, SDL_FLIP_NONE);

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
