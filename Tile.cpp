#include "Tile.h"

void Tile::Render()
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	SDL_Rect rect;
	Vec3 topLeftScreenCoords;
	Vec3 bottomRightScreenCoords;
	Vec3 topLeftWorld;
	Vec3 bottomRightWorld;

	// node position is at center of tile
	Vec3 pos = node->getPos();
	topLeftWorld = Vec3(pos.x - 0.5f * width, pos.y + 0.5 * height, 0.0f);
	bottomRightWorld = Vec3(pos.x + 0.5f * width, pos.y - 0.5 * height, 0.0f);

	topLeftScreenCoords = scene->getProjectionMatrix() * topLeftWorld;
	bottomRightScreenCoords = scene->getProjectionMatrix() * bottomRightWorld;

	rect.x = static_cast<int>(topLeftScreenCoords.x);
	rect.y = static_cast<int>(topLeftScreenCoords.y);
	rect.w = static_cast<int>(bottomRightScreenCoords.x - topLeftScreenCoords.x);
	rect.h = static_cast<int>(bottomRightScreenCoords.y - topLeftScreenCoords.y);

	// draw the tile (you could use images and textures here if you want)
	setRGBA(17, 138, 178, 255);		// blue-green colour
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);

	// draw the border around the tile
	setRGBA(255, 255, 255, 255);	// white
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRect(renderer, &rect);

}