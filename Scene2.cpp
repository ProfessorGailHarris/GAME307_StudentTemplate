#include "Scene2.h"

void Scene2::createTiles()
{
	singleTile = new Tile(2.0, 1.0, this);
}

Scene2::Scene2(SDL_Window* sdlWindow, GameManager* game_)
{
	window = sdlWindow;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
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

	createTiles();

	// let's set up a graph and test it out
	int count = 5;
	sceneNodes.resize(count);
	// create some nodes
	// TODO delete them later
	for (int i = 0; i < count; i++)
	{
		sceneNodes[i] = new Node(i);
	}

	// create the graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		return false;
		// i'm lazy about error messages
	}

	//               0
	//               |
	//      1 -------2 ---------3
	//               |
	//               4

	graph->addWeightedConnection(
		sceneNodes[0]->getLabel(),
		sceneNodes[2]->getLabel(),
		1.0f
	);

	graph->addWeightedConnection(1, 2, 1.0f);

	graph->addWeightedConnection(2, 0, 1.0f);
	graph->addWeightedConnection(2, 1, 1.0f);
	graph->addWeightedConnection(2, 3, 1.0f);
	graph->addWeightedConnection(2, 4, 1.0f);

	graph->addWeightedConnection(3, 2, 1.0f);

	graph->addWeightedConnection(4, 2, 1.0f);

	std::cout << "Scene 2" << std::endl;

	int myNode = 2;

	std::cout << "Neighbours of " << myNode << std::endl;

	for (int nodeLabel : graph->neighbours(myNode))
	{
		std::cout << "node " << nodeLabel << std::endl;
	}

	std::vector<int> path = graph->Dijkstra(0, 4);

	return true;
}

void Scene2::OnDestroy()
{
	// TODO memory cleanup
}

void Scene2::Update(const float time)
{
}

void Scene2::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render tiles
	singleTile->Render();

	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
}
