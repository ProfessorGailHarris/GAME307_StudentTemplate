#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <list>
#include "Condition.h"

class Transition;

using namespace std;

enum class STATE {SEEK, DO_NOTHING};

// TODO destructors, consider for all classes in this file

class State
{
private:
	list<Transition*> transitions;
	STATE name;

public:
	State(STATE name_);
	list<Transition*> getTransitions();
	void addTransition(Transition* transition);
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
	// TODO: do I need constructors?
	void update();
	STATE getCurrentStateName();
	void setInitialState(State* initial_);
};

#endif
