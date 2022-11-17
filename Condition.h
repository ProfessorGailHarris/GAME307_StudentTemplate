#ifndef CONDITION_H
#define CONDITION_H

// abstract class (has a pure virtual function)

// this is circular dependency
//#include "Character.h"

class Condition
{
protected:
	class Character* owner;

public:
	Condition(Character* owner_) { owner = owner_; }
	~Condition(){}
	virtual bool test() = 0;
};

#endif
