#include "Decision.h"

DecisionTreeNode* Decision::makeDecision()
{
    DecisionTreeNode* branch = getBranch();
    return branch->makeDecision();
}

bool Decision::testValue()
{
    return false;
}

DecisionTreeNode* Decision::getBranch()
{
    if (testValue())
    {
        return trueBranch;
    }
    else
    {
        return falseBranch;
    }
}
