#ifndef NODE_H
#define NODE_H

#include "MMath.h"

using namespace std;
using namespace MATH;

class Tile;

class Node
{
private:
	int		label;
	Vec3	position;
	Tile* tile;

public:
	Node(int label_, Vec3 position_ = Vec3())
	{
		label = label_;
		position = position_;
		tile = NULL;
	}
	~Node() {}
	int getLabel() { return label; }
	Vec3 getPos() { return position; }
	void setTile(Tile* tile_) { tile = tile_; }
	Tile* getTile() { return tile; }
};

#endif
