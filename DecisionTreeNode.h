#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

//abstract class
//#include "Character.h"

class Character;

class DecisionTreeNode
{
private:

protected:
	Character* owner;

public:
	virtual DecisionTreeNode* makeDecision() = 0;
};

#endif
