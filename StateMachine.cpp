#include "StateMachine.h"


void StateMachine::update()
{
	Transition* triggered = NULL;
	for (Transition* t : currentState->getTransitions())
	{
		if (t->isTriggered())
		{
			triggered = t;
			break;
		}
	}

	// TODO if you want actions, need to add all the action stuff
	if (triggered)
	{
		currentState = triggered->getTargetState();
		return;
	}
	else
	{
		return;
	}
}

STATE StateMachine::getCurrentStateName()
{
	return currentState->getName();
}

void StateMachine::setInitialState(State* initial_)
{ 
	initialState = initial_; 
	currentState = initialState;
}

State::State(STATE name_)
{ 
	name = name_; 
}

list<Transition*> State::getTransitions()
{
	return transitions;
}

void State::addTransition(Transition* transition)
{ 
	transitions.push_back(transition); 
}

STATE State::getName()
{
	return name;
}

Transition::Transition(Condition* condition_, State* targetState_)
{
	condition = condition_;
	targetState = targetState_;
}

bool Transition::isTriggered()
{
	return condition->test();
}

State* Transition::getTargetState()
{
	return targetState;
}