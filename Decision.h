#ifndef DECISION_H
#define DECISION_H

#include "DecisionTreeNode.h"
class Decision :
    public DecisionTreeNode
{
protected:
    const class Character* owner;
    DecisionTreeNode* trueNode;
    DecisionTreeNode* falseNode;

public:
    virtual DecisionTreeNode* makeDecision();
    virtual bool testValue() = 0;
    virtual DecisionTreeNode* getBranch();
};

#endif
