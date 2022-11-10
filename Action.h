#ifndef ACTION_H
#define ACTION_H

#include "DecisionTreeNode.h"
class Action :
    public DecisionTreeNode
{
public:
    void makeDecision();
};

#endif
