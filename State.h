#ifndef STATE_H
#define STATE_H

#include <list>
#include "Transition.h"

using namespace std;

class Transition;

enum class STATE { SEEK, DO_NOTHING};

class State
{
private:
	list<Transition*> transitions;
	// ignoring Actions for this simple example
	STATE name;

public:
	State(STATE name_) { name = name_; }
	~State() {}
	list<Transition*> getTransitions() { return transitions; }
	void addTransition(Transition* transition);
	STATE getName() { return name; }
};

#endif
