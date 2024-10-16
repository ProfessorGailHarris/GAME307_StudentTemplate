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


	// create a graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		//TODO error message
		return false;
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

	sceneNodes.resize(cols * rows);

	Node* n;
	int label = 0;
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
			n = new Node(label);
			sceneNodes[label] = n;
			Vec3 tilePos = Vec3(x, y, 0.0f);
			t = new Tile(n, tilePos, tileWidth, tileHeight, this);
			tiles[i][j] = t;
			// i or j?
			j++;
			label++;
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
