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
    virtual void makeDecision();
    virtual bool testValue();
    virtual DecisionTreeNode* getbranch();

};

#endif
