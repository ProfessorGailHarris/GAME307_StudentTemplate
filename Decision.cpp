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

void Decision::makeDecision()
{
//	std::cout << "make decision";
	DecisionTreeNode *branch = getbranch();
	branch->makeDecision();
}
