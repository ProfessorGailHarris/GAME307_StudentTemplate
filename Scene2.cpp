#include "Scene2.h"

using namespace std;

Scene2::Scene2(SDL_Window* sdlWindow, GameManager* game_)
{
	window = sdlWindow;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

void Scene2::createTiles()
{

	singleTile = new Tile(2.0f, 1.0f, this);

}

bool Scene2::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	// let's set up a graph and test it out

	int count = 5;
	sceneNodes.resize(count);
	
	//create some nodes
	// TODO delete them later!!!
	for (int i = 0; i < count; i++)
	{
		sceneNodes[i] = new Node(i);
	}

	// create the graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		return false;
		// I'm being lazy about error message here
	}

	//         0
	//         |
	//   1 --- 2 --- 3
	//         |
	//         4

	// connections from 0
	graph->addWeightConnection(
		sceneNodes[0]->getLabel(),
		sceneNodes[2]->getLabel(),
		1.0f
	);

	//connections from 1
	graph->addWeightConnection(1, 2, 1.0f);

	// connections from 2
	graph->addWeightConnection(2, 0, 1.0f);
	graph->addWeightConnection(2, 1, 1.0f);
	graph->addWeightConnection(2, 3, 1.0f);
	graph->addWeightConnection(2, 4, 1.0f);

	// connections from 3
	graph->addWeightConnection(3, 2, 1.0f);

	// connections from 4
	graph->addWeightConnection(4, 2, 1.0f);

	cout << "Scene 2" << endl;
	int myNode = 0;

	cout << "neighbours of " << myNode << endl;
	for (auto nodeLabel : graph->neighbours(myNode))
	{
		cout << "node " << nodeLabel << endl;
	}


	createTiles();

	// call dijsktra
	vector<int> path = graph->Dijkstra(0, 4);

	return true;
}

void Scene2::OnDestroy()
{
	// memory clean up
}

void Scene2::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	singleTile->Render();

	SDL_RenderPresent(renderer);
}
 
