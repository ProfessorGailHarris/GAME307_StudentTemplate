#ifndef DECISION_H
#define DECISION_H

#include "DecisionTreeNode.h"
class Decision :
    public DecisionTreeNode
{
protected:
    DecisionTreeNode* trueNode;
    DecisionTreeNode* falseNode;

public:
    virtual DecisionTreeNode* makeDecision();
    virtual bool testValue();
    virtual DecisionTreeNode* getbranch();

};

#endif
