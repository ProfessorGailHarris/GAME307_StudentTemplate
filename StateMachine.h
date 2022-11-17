#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"
#include "Transition.h"
#include "Condition.h"
#include "ConditionInRange.h"
#include "ConditionOutOfRange.h"

// circular dependency
//#include "Character.h"
// and any other conditions


class StateMachine
{
private:
	State* initialState;
	State* currentState;
	class Character* owner;

public:
	StateMachine(Character* owner_) { owner = owner_; }
	~StateMachine() {}
	void setInitialState(State* initial_);
	void update();
	STATE getCurrentStateName() { return currentState->getName(); }
};

#endif
