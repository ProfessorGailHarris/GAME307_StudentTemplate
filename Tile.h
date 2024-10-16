#ifndef TILE_H
#define TILE_H

#include "Scene.h"
#include "Node.h"


class Tile
{
private:
	float width, height;
	Uint8 r, g, b, a;
	Vec3 pos;
	Node* node;
	Scene* scene;

	void setRGBA(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_)
	{
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}

public:
	Tile(Node* node_, Vec3 pos_, float width_, float height_, Scene* scene_);
	virtual ~Tile() {}
	void Render();
	Node* getNode() const { return node; }
};

#endif
