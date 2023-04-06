#ifndef CONDITION_H
#define CONDITION_H

class Condition
{
protected:
	const class Character* owner;

public:
	Condition(Character* owner_) { owner = owner_; }

	virtual bool test() = 0;
};

#endif
