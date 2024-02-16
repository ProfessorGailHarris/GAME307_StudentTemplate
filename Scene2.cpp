#include "Scene2.h"

Scene2::Scene2(SDL_Window* sdlWindow, GameManager* game_)
{
	window = sdlWindow;
	game = game_;
	renderer = SDL_GetRenderer(window);
	graph = NULL;
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene2::~Scene2()
{
}

void Scene2::createTiles()
{
	singleTile = new Tile(Vec3(4.5f, 8.2f, 0.0f), 2.0, 1.0, this);
}

bool Scene2::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w,h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	createTiles();

	// let's set up a graph and test it out
	int count = 5;
	sceneNodes.resize(count);
	// create some nodes, remember to delete them later

	for (int i = 0; i < count; i++)
	{
		sceneNodes[i] = new Node(i);
	}

	//create the graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		// TODO error message
		return false;
	}

	//                        4
	//                        |
	//         1  ----------- 2 ------------ 3
	//                        |
	//                        0

	// TODO use addWeightedConnection to create this graph
	graph->addWeightedConnection(graph->getNode(2), graph->getNode(0), 1.0f);
	graph->addWeightedConnection(graph->getNode(2), graph->getNode(1), 1.0f);
	graph->addWeightedConnection(graph->getNode(2), graph->getNode(3), 1.0f);
	graph->addWeightedConnection(graph->getNode(2), graph->getNode(4), 1.0f);

	graph->addWeightedConnection(graph->getNode(4), graph->getNode(2), 1.0f);
	graph->addWeightedConnection(graph->getNode(1), graph->getNode(2), 1.0f);
	graph->addWeightedConnection(graph->getNode(3), graph->getNode(2), 1.0f);
	graph->addWeightedConnection(graph->getNode(0), graph->getNode(2), 1.0f);


	// TODO debug, print out the neighbours of some node
	int myNode = 2;
	std::cout << "Neighbours of " << myNode << "\n";

	for (Node* n : graph->neighbours(graph->getNode(myNode)))
	{
		std::cout << "node " << n->getLabel() << "\n";
	}

	std::vector<Node*> path = graph->findPath(
		sceneNodes[0],
		sceneNodes[4]
	);

	return true;
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
