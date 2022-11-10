#include "Decision.h"

DecisionTreeNode* Decision::getbranch()
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

bool Decision::testValue()
{
	return false;
}

DecisionTreeNode* Decision::makeDecision()
{
	DecisionTreeNode *branch = getbranch();
	return branch->makeDecision();
}
