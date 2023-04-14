#include "CharacterAdapter.h"

CharacterAdapter::CharacterAdapter(Character* adaptee_)
{
	adaptee = adaptee_;
}

Vec3 CharacterAdapter::getPlayerPos()
{
	return adaptee->getPlayerPos();
}

Vec3 CharacterAdapter::getPos()
{
	return adaptee->getPos();
}
