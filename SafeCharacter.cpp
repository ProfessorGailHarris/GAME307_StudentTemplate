#include "SafeCharacter.h"

SafeCharacter::SafeCharacter(Character* adaptee_)
{
	adaptee = adaptee_;
}

Vec3 SafeCharacter::getPlayerPos()
{
	return adaptee->getPlayerPos();
}

Vec3 SafeCharacter::getPos()
{
	return adaptee->getPos();
}
