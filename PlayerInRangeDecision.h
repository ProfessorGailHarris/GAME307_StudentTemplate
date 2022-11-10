#ifndef PLAYERINRANGEDECISION_H
#define PLAYERINRANGEDECISION_H

#include "Decision.h"

class PlayerInRangeDecision :
    public Decision
{
public:

    PlayerInRangeDecision(Character* owner_, DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_)
    {
        owner = owner_;
        trueNode = trueNode_;
        falseNode = falseNode_;
    }

    bool testValue();
};

#endif
