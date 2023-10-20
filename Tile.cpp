 #include "Tile.h"

Tile::Tile(Node* node_, Vec3 pos_, float width_, float height_, Scene* scene_)
{
	node = node_;
	pos = pos_;
	width = width_;
	height = height_;
	r = 0;
	g = 255;
	b = 255;
	a = 255;
	scene = scene_;
}

void Tile::Render()
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	SDL_Rect rect;

	Vec3 topLeft;
	Vec3 bottomRight;

	Vec3 topLeftScreen;
	Vec3 bottomRightScreen;

	// the center of the tile
	topLeft = Vec3(pos.x - 0.5 * width, pos.y + 0.5 * height, 0.0f);
	bottomRight = Vec3(pos.x + 0.5 * width, pos.y - 0.5 * height, 0.0f);

	topLeftScreen = scene->getProjectionMatrix() * topLeft;
	bottomRightScreen = scene->getProjectionMatrix() * bottomRight;

	rect.x = static_cast<int>(topLeftScreen.x);
	rect.y = static_cast<int>(topLeftScreen.y);
	rect.w = static_cast<int>(bottomRightScreen.x - topLeftScreen.x);
	rect.h = static_cast<int>(bottomRightScreen.y - topLeftScreen.y);

	// draw the tile (you could use images and textures)
	setRGBA(17, 138, 178, 255);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);

	// draw a border around the tile
	setRGBA(255, 255, 255, 255);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRect(renderer, &rect);
}
