#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

class DecisionTreeNode
{
public:
	virtual DecisionTreeNode* makeDecision() = 0;
};

#endif // DECISIONTREENODE_H
