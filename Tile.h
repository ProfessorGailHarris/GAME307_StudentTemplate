#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"

class Tile
{
private:
	float width;
	float height;
	Uint8 r, g, b, a;
	Scene* scene;

	void setRGBA(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_)
	{
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}

public:
	Tile(float width_, float height_, Scene* scene_);
	~Tile() {}
	void Render();
};

#endif
