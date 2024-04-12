#include "SafeCharacter.h"

Vec3 SafeCharacter::getPlayerPos()
{
	return adaptee->getPlayerPos();
}

Vec3 SafeCharacter::getPos()
{
	return adaptee->getPos();
}
