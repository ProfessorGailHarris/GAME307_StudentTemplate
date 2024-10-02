#ifndef NODE_H
#define NODE_H

class Node
{
private:
	int label;

public:
	Node(int label_) : label{ label_ } {};
	~Node() {}

	int getLabel() { return label; };
};

#endif
