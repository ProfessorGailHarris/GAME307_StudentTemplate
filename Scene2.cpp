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
	int window_w, window_h;
	SDL_GetWindowSize(window, &window_w, &window_h);

	Matrix4 ndc = MMath::viewportNDC(window_w, window_h);
	Matrix4	ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	inverseProjection = MMath::inverse(projectionMatrix);

	// turn on SDL imaging
	IMG_Init(IMG_INIT_PNG);

	// create a tile with a node
	int cols = ceil(xAxis / tileWidth);
	int rows = ceil(yAxis / tileHeight);
	createTiles(rows, cols);
	// this createTiles is also going to populate nodes list


	//create the graph, an empty graph
	graph = new Graph();
	if (!graph->OnCreate(nodes))
	{
		printf("graph OnCreate failed. \n");
		return false;
	}

	calculateConnectionWeights();

	return true;
}

void Scene2::createTiles(int rows, int cols)
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
		//do stuff for a row, where y stays constant
		for (float x = 0.5 * tileWidth; x < xAxis; x += tileWidth)
		{
			n = new Node(label, Vec3(x, y, 0.0f));
			t = new Tile(n, tileWidth, tileHeight, this);
			n->setTile(t);
			nodes.push_back(n);
			tiles[i][j] = t;

			label++;
			j++;
		}
		j = 0;
		i++;
	}
}

void Scene2::calculateConnectionWeights()
{
	int rows = tiles.size();
	int cols = tiles[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//                 i+1,j
			//   i, j-1          i,j        i, j+1
			//                 i-1,j

			int from = tiles[i][j]->getNode()->getLabel();

			//left is i, j-1
			if (j>0)
			{
				int to = tiles[i][j - 1]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileWidth);
			}
			//right is i,j+1
			if (j < cols - 1)
			{
				int to = tiles[i][j + 1]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileWidth);
			}
			//above is i+1,j
			if (i < rows - 1)
			{
				int to = tiles[i+1][j]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileWidth);
			}
			//below is i-1,j
			if (i > 0)
			{
				int to = tiles[i-1][j]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileWidth);
			}

		}
	}
}


void Scene2::OnDestroy() 
{
	// TODO delete nodes
}

void Scene2::Update(const float deltaTime)
{}

void Scene2::Render()
{
	// clear the frame
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

	// render it all
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(
	const SDL_Event& event
)
{}

