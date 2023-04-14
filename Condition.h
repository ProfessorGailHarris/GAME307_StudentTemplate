#ifndef CONDITION_H
#define CONDITION_H

class Condition
{
protected:
	class CharacterAdapter* owner;

public:
	Condition(CharacterAdapter* owner_) { owner = owner_; }

	virtual bool test() = 0;
};

#endif
