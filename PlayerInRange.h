#ifndef PLAYERINRANGE_H
#define PLAYERINRANGE_H

#include "Decision.h"

class PlayerInRange :
    public Decision
{
    public:
	PlayerInRange() : Decision() {}
	PlayerInRange( DecisionTreeNode * trueBranch_, DecisionTreeNode * falseBranch_, Character* owner_) 
		: Decision(trueBranch_, falseBranch_, owner_) {}
	~PlayerInRange() {}

	bool testValue();
};

#endif // !PLAYERINRANGE_H
