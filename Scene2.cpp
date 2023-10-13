#include "Scene2.h"

Scene2::Scene2(SDL_Window* sdlWindow, GameManager* game_)
{
	window = sdlWindow;
	game = game_;
	renderer = SDL_GetRenderer(window);
}

Scene2::~Scene2()
{
}

bool Scene2::OnCreate()
{
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
}

void Scene2::HandleEvents(const SDL_Event& event)
{
}
