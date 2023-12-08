#ifndef SAFECHARACTER_H
#define SAFECHARACTER_H

#include "Character.h"

class Character;

class SafeCharacter
{
private: 
	Character* adaptee;

public:
	//Constructor
	SafeCharacter(Character* adaptee_);

	Vec3 getPlayerPos();
	Vec3 getPos();

};

#endif
