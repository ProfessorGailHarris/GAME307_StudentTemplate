#include "Tile.h"

Tile::Tile(Node* node_, Vec3 pos_, float width_, float height_, Scene* scene_) :
node{node_}, pos{pos_}, width{width_}, height{height_}
{
	r = 0;
	g = 255;
	b = 255;
	a = 255;
	scene = scene_;	
}

void Tile::Render()
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;

	Vec3 topLeft, bottomRight;
	Vec3 topLeftScreen, bottomRightScreen;

	topLeft = Vec3(pos.x - 0.5 * width, pos.y + 0.5 * height, 0.0f);
	bottomRight = Vec3(pos.x + 0.5*width, pos.y - 0.5*height, 0.0f);

	topLeftScreen = projectionMatrix * topLeft;
	bottomRightScreen = projectionMatrix * bottomRight;

	square.x = static_cast<int>(topLeftScreen.x);
	square.y = static_cast<int>(topLeftScreen.y);
	square.w = static_cast<int>(bottomRightScreen.x - topLeftScreen.x);
	square.h = static_cast<int>(bottomRightScreen.y - topLeftScreen.y);
	
	setRGBA(17, 138, 178, 255);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &square);

	// draw a border around the tile
	setRGBA(255, 255, 255, 255);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRect(renderer, &square);

}

