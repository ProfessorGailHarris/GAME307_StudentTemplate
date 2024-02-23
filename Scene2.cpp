#include "Scene2.h"

Scene2::Scene2(SDL_Window* sdlWindow, GameManager* game_)
{
	window = sdlWindow;
	game = game_;
	renderer = SDL_GetRenderer(window);
	graph = NULL;
	xAxis = 25.0f;
	yAxis = 15.0f;
	tileWidth = 0.0;
	tileHeight = 0.0;
}

Scene2::~Scene2()
{
}

void Scene2::createTiles()
{
	tileWidth = 4.0f;
	tileHeight = 3.5f;

	// resize tiles[][] 
	int cols = ceil( (xAxis - 0.5f*tileWidth) / tileWidth );
	int rows = ceil( (yAxis - 0.5f*tileHeight) / tileHeight );

	tiles.resize(rows);
	for (int i=0; i < rows; i++)
	{
		tiles[i].resize(cols);
	}

	sceneNodes.resize(cols * rows);

	Node * n;
	int label = 0;
	Tile * t;
	int i, j;

	i = 0;
	j = 0;

	for (float y = 0.5f * tileHeight; y < yAxis; y += tileHeight)
	{
		// do stuff as y increases
		for (float x = 0.5f * tileWidth; x < xAxis; x += tileWidth)
		{
			// do stuff as x increases
			n = new Node(label);
			sceneNodes[label] = n;
			// create tile
			Vec3 tilePos = Vec3(x, y, 0.0f);
			t = new Tile(n, tilePos, tileWidth, tileHeight, this);
			tiles[i][j] = t;
			j++;
			label++;
		}
		j=0;
		i++;
	}
}

void Scene2::calculateConnectionWeights()
{
	// I'm smart enough to only call this
	// after having properly created the tiles matrix
	int rows = tiles.size();
	int cols = tiles[0].size();

	for( int i=0; i < rows; i++)
	{
		for( int j=0; j < cols; j++)
		{
		//tiles[i][j]->getNode();
		//
		//          i+1, j
		//   i,j-1    i, j      i,j+1
		//          i-1, j
		Tile* fromTile = tiles[i][j];
		Node* from = fromTile->getNode();

		// left
		if ( j > 0 )
		{
			Node* to = tiles[i][j-1]->getNode();
			graph->addWeightedConnection(from, to, tileWidth);
		}

		// right

		// above
		if ( i < rows - 1 )
		{
			Node* to = tiles[i+1][j]->getNode();
			graph->addWeightedConnection(from, to, tileHeight);
		}

		// below
		}
	}
}

bool Scene2::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w,h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	createTiles();

	//create the graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		// TODO error message
		return false;
	}

	calculateConnectionWeights();

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

	for (int i=0; i < tiles.size(); i++)
	{
		for (int j=0; j < tiles[i].size(); j++)
		{
			tiles[i][j]->Render();
		}
	}
	
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
}
