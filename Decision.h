#ifndef DECISION_H
#define DECISION_H

#include "DecisionTreeNode.h"
#include "Action.h"

class Decision :
    public DecisionTreeNode
{
protected:
	DecisionTreeNode* trueBranch;
	DecisionTreeNode* falseBranch;
	class Character* owner;

public:
	// this should never be called
	Decision() : trueBranch{ nullptr }, falseBranch{ nullptr }, owner{ nullptr }
	{}

	Decision(DecisionTreeNode* trueBranch_, DecisionTreeNode* falseBranch_, Character* owner_) : 
		trueBranch{ trueBranch_ }, 
		falseBranch{ falseBranch_ },
		owner{ owner_ }
	{}

	virtual bool testValue();
	virtual DecisionTreeNode* getBranch();
	virtual DecisionTreeNode* makeDecision();
};

#endif // !DECISION_H
