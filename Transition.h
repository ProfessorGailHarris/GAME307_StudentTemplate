#ifndef TRANSITION_H
#define TRANSITION_H

//#include "State.h"
#include "Condition.h"


class Transition
{
private: 
	// ignoring action for this demo
	class State* targetState;
	class Condition* condition;

public:
	Transition(Condition* condition_, State* targetState_);
	~Transition();
	bool isTriggered();
	State* getTargetState() { return targetState; }
};

#endif
