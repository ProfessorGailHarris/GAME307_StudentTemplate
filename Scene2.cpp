#include "Scene2.h"

Scene2::Scene2(
	SDL_Window* sdlWindow_,
	GameManager* game_
)
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
	// let's set up  a graph and test it out
	//         0
	//         |
	//   1 --- 2 --- 3
	//         |
	//         4

	int count = 5;
	nodes.resize(count);
	
	// create the nodes
	for (int i = 0; i < count; i++)
	{
		nodes[i] = new Node(i);
	}
	// since Nodes are created here, then the scene
	// is responsible for deleting them later!!!!

	//create the graph, an empty graph
	graph = new Graph();
	if (!graph->OnCreate(nodes))
	{
		printf("graph OnCreate failed. \n");
		return false;
	}

	// connections from 0
	graph->addWeightConnection(
		nodes[0]->getLabel(),
		nodes[2]->getLabel(),
		1.0f
	);

	// connections from 1
	graph->addWeightConnection(
		nodes[1]->getLabel(),
		nodes[2]->getLabel(),
		1.0f
	);

	// conectsion from 2
	graph->addWeightConnection(
		nodes[2]->getLabel(),
		nodes[0]->getLabel(),
		1.0f
	);
	graph->addWeightConnection(
		nodes[2]->getLabel(),
		nodes[1]->getLabel(),
		1.0f
	);
	graph->addWeightConnection(
		nodes[2]->getLabel(),
		nodes[3]->getLabel(),
		1.0f
	);
	graph->addWeightConnection(
		nodes[2]->getLabel(),
		nodes[4]->getLabel(),
		1.0f
	);

	// connections from 3
	graph->addWeightConnection(
		nodes[3]->getLabel(),
		nodes[2]->getLabel(),
		1.0f
	);

	// connections from 4
	graph->addWeightConnection(
		nodes[4]->getLabel(),
		nodes[2]->getLabel(),
		1.0f
	);

	printf("Scene2:\n");

	//graph->neighbours(1);
	int nodeLabel;
	printf("neighbours of 2: \n");
	for (auto nodeLabel : graph->neighbours(2))
	{
		printf("node %i, ", nodeLabel);
	}
	printf("\n");

	return true;
}

void Scene2::OnDestroy() 
{
	// TODO delete nodes
}

void Scene2::Update(const float deltaTime)
{}

void Scene2::Render()
{}

void Scene2::HandleEvents(
	const SDL_Event& event
)
{}

