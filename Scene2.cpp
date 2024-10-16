#include "Scene2.h"

Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	tileWidth = 0.0f;
	tileHeight = 0.0f;
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

	std::vector<Node*> path = graph->findPath(
		sceneNodes[0],
		sceneNodes[4]
	);

    return true;
}

void Scene2::createTiles()
{
	tileWidth = 3.0f;
	tileHeight = 2.0f;

	// resize tiles[][]
	int cols = ceil((xAxis - 0.5f * tileWidth) / tileWidth);
	int rows = ceil((yAxis - 0.5f * tileHeight) / tileHeight);

	tiles.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		tiles[i].resize(cols);
	}

	Tile* t;
	int i, j;

	i = 0;
	j = 0;

	for (float y = 0.5f * tileHeight; y < yAxis; y += tileHeight)
	{
		// do stuff as y increases
		for (float x = 0.5f * tileWidth; x < xAxis; x += tileWidth)
		{
			//do stuff as x increases
			// create tile
			Vec3 tilePos = Vec3(x, y, 0.0f);
			t = new Tile(tilePos, tileWidth, tileHeight, this);
			tiles[i][j] = t;
			// i or j?
			j++;
		}
		j = 0;
		i++;
	}
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

	for (int i=0; i < tiles.size(); i++)
		for (int j = 0; j < tiles[i].size(); j++)
		{
			tiles[i][j]->Render();
		}

	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
}
