#ifndef CONDITION_H
#define CONDITION_H

#include <VMath.h>

class Condition
{
protected:
	class SafeCharacter* owner;

public:
	Condition(SafeCharacter* owner_) : owner{ owner_ }
	{}

	virtual bool test() = 0;
};

class ConditionOutOfRange : public Condition
{
public:
	ConditionOutOfRange(SafeCharacter* owner_) : Condition{ owner_ }
	{}

	bool test();
};

class ConditionInRange : public Condition
{
public:
	ConditionInRange(SafeCharacter* owner_) : Condition{ owner_ }
	{}

	bool test();
};

#endif
