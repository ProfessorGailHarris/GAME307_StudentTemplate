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

void Scene2::createTiles(int rows, int cols)
{
	tiles.resize(rows);
	for ( int i=0; i < rows; i++)
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
		// do stuff for a row, where y stays constant
		for (float x = 0.5f*tileWidth; x < xAxis; x += tileWidth)
		{
			// create tiles and nodes
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
	int rows = tiles.size();
	int cols = tiles[0].size();

	for (int i=0; i < rows; i++)
	{
		for (int j=0; j < cols; j++)
		{

		//               i+1, j
		//    i,j-1        i, j          i, j+1
		//               i-1, j

		Tile* fromTile = tiles[i][j];
		int from = fromTile->getNode()->getLabel();

		// left is i, j-1
		if (j>0)
		{
			int to = tiles[i][j-1]->getNode()->getLabel();
			graph->addWeightConnection(from, to, tileWidth);
		}

		// right is i, j+1
		if (j < cols - 1)
		{
			int to = tiles[i][j+1]->getNode()->getLabel();
			graph->addWeightConnection(from, to, tileWidth);
		}

		// above is i+1, j
		if ( i < rows - 1 )
		{
			int to = tiles[i+1][j]->getNode()->getLabel();
			graph->addWeightConnection(from, to, tileHeight);
		}

		// below is i-1, j
		if ( i > 0 )
		{
			int to = tiles[i-1][j]->getNode()->getLabel();
			graph->addWeightConnection(from, to, tileHeight);
		}

		}
	}
}

bool Scene2::OnCreate()
{
	tileWidth = 5.0f;
	tileHeight = 3.0f;
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	// calculate rows and cols
	int cols = ceil ( (xAxis - 0.5f * tileWidth) / tileWidth );
	int rows = ceil ( (yAxis - 0.5f * tileHeight) / tileHeight );
	createTiles(rows, cols);

	// create the graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		cerr << "problem creating nodes" << endl;
		return false;
	}


	// create connections
	calculateConnectionWeights();

	// call dijsktra
	vector<int> path = graph->Dijkstra(0, 4);

	// check correctness
	vector<int> testNodes = {};
	//testNodes = {0, 3, 4, 10, 12, 14, 20, 22, 24};
	for (auto myNode : testNodes )
	{
	cout << endl << "neighbours of " << myNode << endl;
	for( auto nodeLabel : graph->neighbours(myNode))
		cout << "node " << nodeLabel << endl;
	}

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

	// render all tiles
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			tiles[i][j]->Render();
		}
	}

	SDL_RenderPresent(renderer);
}
 
