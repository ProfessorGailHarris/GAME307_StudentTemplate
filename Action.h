#ifndef ACTION_H
#define ACTION_H

#include "DecisionTreeNode.h"

enum class ACTION_SET { SEEK, DO_NOTHING };

class Action :
    public DecisionTreeNode
{
private:
    ACTION_SET value;

public:
    Action(ACTION_SET value_) { value = value_; }
    virtual DecisionTreeNode* makeDecision();
    virtual ACTION_SET getValue() { return value; }
};

#endif
