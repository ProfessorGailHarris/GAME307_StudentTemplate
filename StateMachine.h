#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <list>
#include "Condition.h"

enum class STATE {DO_NOTHING, SEEK, ARRIVE, FLEE, PURSUE, SLEEP, EAT};

class Transition;

class State
{
private: 
	std::list<Transition*> transitions;
	STATE name;

public:
	State(STATE name_);
	std::list<Transition*> getTransitions();
	void addTransition(Transition* transition_);
	STATE getName();
};

class Transition
{
private:
	Condition* condition;
	State* targetState;

public:
	Transition(Condition* condition_, State* targetState_);
	bool isTriggered();
	State* getTargetState();
};

class StateMachine
{
private:
	State* initialState;
	State* currentState;

public:
	// default constructor only
	void update();
	STATE getCurrentStateName();
	void setInitialState(State* initial_);
};

#endif
