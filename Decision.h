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
	Decision() { trueBranch = nullptr; falseBranch = nullptr; owner = nullptr; }
	Decision(DecisionTreeNode* trueBranch_, DecisionTreeNode* falseBranch_, Character* owner_)
	{
		trueBranch = trueBranch_;
		falseBranch = falseBranch_;
		owner = owner_;
	}
	~Decision() {}

	virtual DecisionTreeNode* makeDecision();
	virtual bool testValue();
	virtual DecisionTreeNode* getBranch();

};

#endif // !DECISION_H
