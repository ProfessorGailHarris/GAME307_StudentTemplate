#ifndef CONDITION_H
#define CONDITION_H

#include <VMath.h>

class Condition
{
protected:
	class Character* owner;

public:
	Condition(Character* owner_)
	{
		owner = owner_;
	}

	virtual bool test() = 0;
};


class ConditionIfInRange : public Condition
{
public:
	ConditionIfInRange(Character* owner_) : Condition{ owner_ }
	{

	}

	bool test();
};

class ConditionOutOfRange : public Condition
{
public:
	ConditionOutOfRange(Character* owner_) : Condition{ owner_ }
	{

	}

	bool test();
};


#endif
