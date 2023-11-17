#include "StateMachine.h"

State::State(STATE name_)
{
    name = name_;
}

std::list<Transition*> State::getTransitions()
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

void StateMachine::update()
{
    Transition* triggered = NULL;
    for (auto t : currentState->getTransitions())
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
        // collect up the actions
        // (see the slide)
        currentState = targetState;
        return;
    }

    return;
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
