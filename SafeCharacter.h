#ifndef SAFE_CHARACTER_H
#define SAFE_CHARACTER_H

class Character;

#include "Character.h"

class SafeCharacter
{
private:
	Character* adaptee;

public:
	SafeCharacter(Character* adaptee_) : adaptee{ adaptee_ } {};

	Vec3 getPlayerPos();
	Vec3 getPos();
};

#endif
