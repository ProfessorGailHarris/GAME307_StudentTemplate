#ifndef ACTION_H
#define ACTION_H

#include "DecisionTreeNode.h"

enum class ACTION_SET {SEEK, DO_NOTHING};

class Action :
    public DecisionTreeNode 
{
private:
    ACTION_SET label;

public:
	Action() { label = ACTION_SET::DO_NOTHING; }
    Action(ACTION_SET label_) { label = label_; }
	~Action() {}

	DecisionTreeNode* makeDecision() { return this; }
	ACTION_SET getLabel() const { return label; }
};

#endif
