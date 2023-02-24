#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"
#include "Node.h"

class Tile
{
private:

	float width;
	float height;
	Uint8 r, g, b, a;
	Scene* scene;

	Node* node;
	Vec3 pos;

	void setRGBA(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_)
	{
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}

public:

	Tile( Node* node_, Vec3 pos_, float width_, float height_, Scene* scene_);
	~Tile() {}
	void Render();
	Node* getNode() { return node; }

};

#endif

