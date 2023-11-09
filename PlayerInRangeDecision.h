#ifndef PLAYERINRANGEDECISION_H
#define PLAYERINRANGEDECISION_H

#include "Decision.h"
#include <VMath.h>

class PlayerInRangeDecision :
    public Decision
{
public:
    PlayerInRangeDecision() : Decision()
	{}
    
    PlayerInRangeDecision(
        DecisionTreeNode* trueBranch_, 
        DecisionTreeNode* falseBranch_, 
        Character* owner_
    ) :
		Decision(trueBranch_, falseBranch_, owner_)
    {}

    bool testValue();
};

#endif // !PLAYERINRANGEDECISION_H
