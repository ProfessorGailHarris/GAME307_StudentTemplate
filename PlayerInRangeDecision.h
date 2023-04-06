#ifndef PLAYER_IN_RANGE_DECISION_H
#define PLAYER_IN_RANGE_DECISION_H

#include "VMath.h"
#include "Character.h"

class Character;

using namespace MATH;

#include "Decision.h"
class PlayerInRangeDecision :
    public Decision
{
public:
    PlayerInRangeDecision(DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_, Character* owner_)
    {
        trueNode = trueNode_;
        falseNode = falseNode_;
        owner = owner_;
    }

    bool testValue();
};

#endif
