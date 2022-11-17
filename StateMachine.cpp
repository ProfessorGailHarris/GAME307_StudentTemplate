#include "StateMachine.h"

void StateMachine::setInitialState(State* initial_)
{
	initialState = initial_;
	currentState = initialState;
}

void StateMachine::update()
{
	Transition* triggered = NULL;

	// store first transition that triggers
	for (auto transition : currentState->getTransitions())
	{
		if (transition->isTriggered())
		{
			triggered = transition;
			break;
		}
	}
	if (triggered)
	{
		State* targetState = triggered->getTargetState();
		//TODO collect exit actions, transition action, and target state actions
		currentState = targetState;
	}
	else
	{
		//TODO process actions for current state
	}
	// return any actions
	// but I'm not doing actions in this simple demo
	return;
}
