#include "StateMachine.h"

State::State(STATE name_) : name{ name_ }
{}

std::list<Transition*> State::getTransitions()
{
	return transitions;
}

void State::addTransition(Transition* transition_)
{
	transitions.push_back(transition_);
}

STATE State::getName()
{
	return name;
}

Transition::Transition(Condition* condition_, State* targetState_) :
	condition {condition_}, targetState{targetState_}
{
}

bool Transition::isTriggered()
{
	return condition->test();
}

State* Transition::getTargetState()
{
	return targetState;
}

STATE StateMachine::getCurrentStateName()
{
	return currentState->getName();
}

void StateMachine::setInitialState(State* initial_)
{
	initialState = initial_;
	currentState = initial_;
}

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

	if (triggered)
	{
		State* targetState = triggered->getTargetState();
		// skipping the collect up actions
		
		currentState = targetState;
		return;
	}

	return;
}
