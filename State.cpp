#include "State.h"

void State::addTransition(Transition* transition)
{
	transitions.push_back(transition);
}
