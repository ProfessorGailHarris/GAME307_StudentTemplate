#include "Scene2.h"

Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
}

Scene2::~Scene2()
{
}

bool Scene2::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	createTiles();


	// let's set up a graph and test it out
	int count = 5;
	sceneNodes.resize(count);
	//create some nodes remember to delete them later
	for (int i = 0; i < count; i++)
	{
		sceneNodes[i] = new Node(i);
	}

	// create a graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		//TODO error message
		return false;
	}

	//                        4
	//                        |
	//      1 --------------- 2 --------------- 3
	//                        |
	//                        0

	graph->addWeightedConnection(graph->getNode(2), graph->getNode(0), 1.0f);
	graph->addWeightedConnection(graph->getNode(2), graph->getNode(1), 1.0f);
	graph->addWeightedConnection(graph->getNode(2), graph->getNode(3), 1.0f);
	graph->addWeightedConnection(graph->getNode(2), graph->getNode(4), 1.0f);

	graph->addWeightedConnection(graph->getNode(0), graph->getNode(2), 1.0f);
	graph->addWeightedConnection(graph->getNode(1), graph->getNode(2), 1.0f);
	graph->addWeightedConnection(graph->getNode(3), graph->getNode(2), 1.0f);
	graph->addWeightedConnection(graph->getNode(4), graph->getNode(2), 1.0f);


	// debug, print out the neighbours of some node
	int myNode = 1;
	std::cout << "Neighbours of " << myNode << "\n";

	for (Node* n : graph->neighbours(graph->getNode(myNode)))
	{
		std::cout << "node " << n->getLabel() << "\n";
	}

    return true;
}

void Scene2::createTiles()
{
	singleTile = new Tile(Vec3(15.0, 7.7f, 0.0f), 3.0f, 3.0f, this);
}

void Scene2::OnDestroy()
{
}

void Scene2::Update(const float time)
{
}

void Scene2::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	singleTile->Render();

	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
}
