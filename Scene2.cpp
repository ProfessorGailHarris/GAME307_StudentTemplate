#include "Scene2.h"

void Scene2::createTiles(int rows, int cols )
{
	tiles.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		tiles[i].resize(cols);
	}

	Node* n;
	Tile* t;
	int i, j, label;

	i = 0;
	j = 0;
	label = 0;

	for (float y = 0.5f * tileHeight; y < yAxis; y += tileHeight)
	{
		// do stuff for a row, y stays constant
		for (float x = 0.5f * tileWidth; x < xAxis; x += tileWidth)
		{
			//create tiles and nodes
			n = new Node(label);
			sceneNodes.push_back(n);
			Vec3 tilePos = Vec3(x, y, 0.0f);
			t = new Tile(n, tilePos, tileWidth, tileHeight, this);
			tiles[i][j] = t;
			j++;
			label++;
		}
		j = 0;
		i++;
	}
}

void Scene2::calculateConnectionWeights()
{
	// This is a private method
	// I'm assuming I'm smart enough to only call this
	// after having properly created tiles matrix
	int rows = tiles.size();
	int cols = tiles[0].size();

	for( int i=0; i < rows; i++ )
	{
		for( int j=0; j < cols; j++ )
		{
			//          i+1,j
			//   i,j-1    i,j   i,j+1
			//          i-1,j

			Tile* fromTile = tiles[i][j];
			int from = fromTile->getNode()->getLabel();

			// left is i,j-1
			if ( j > 0 )
			{
				int to = tiles[i][j-1]->getNode()->getLabel();
				graph->addWeightedConnection(from, to, tileWidth);
			}

			// right is i,j+1
			if ( j < cols - 1 )
			{
				int to = tiles[i][j+1]->getNode()->getLabel();
				graph->addWeightedConnection(from, to, tileWidth);
			}

			// above is i+1, j
			if ( i < rows - 1 )
			{
				int to = tiles[i+1][j]->getNode()->getLabel();
				graph->addWeightedConnection(from, to, tileHeight);
			}

			// below is i-1, j
			if ( i > 0 )
			{
				int to = tiles[i-1][j]->getNode()->getLabel();
				graph->addWeightedConnection(from, to, tileHeight);
			}

			// N.B. weight of each connection could depend on
			// the context of the "from" or "to" tile.
			// E.g. if a tile is blocked,
			// or represents terrain that is hard to navigate.
		}
	}
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
	tileWidth = 5.0f;
	tileHeight = 3.0f;
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//calculate rows and cols
	int cols = ceil((xAxis - 0.5f * tileWidth) / tileWidth);
	int rows = ceil((yAxis - 0.5f * tileHeight) / tileHeight);
	createTiles(rows, cols);

	// let's set up a graph and test it out

	// create the graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		return false;
		// i'm lazy about error messages
	}

	// create connections
	calculateConnectionWeights();

	// test some connections
	std::cout << "Scene 2" << std::endl;
	std::vector<int> testNodes;
	testNodes = {0, 3, 4, 7, 11, 15, 24};
	auto it = testNodes.begin();
	while( it != testNodes.end() )
	{
		int myNode = (*it);
		std::cout << "neighbours of " << myNode << std::endl;
		for (auto nodeLabel : graph->neighbours(myNode))
		{
			std::cout << "node " << nodeLabel << std::endl;
		}
		it++;
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
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			tiles[i][j]->Render();
		}
	}

	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
}
