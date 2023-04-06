#include "Decision.h"

DecisionTreeNode* Decision::makeDecision()
{
    DecisionTreeNode* branch = getBranch();
    return branch->makeDecision();
}

DecisionTreeNode* Decision::getBranch()
{
    if (testValue())
    {
        return trueNode;
    }
    else
    {
        return falseNode;
    }
}
