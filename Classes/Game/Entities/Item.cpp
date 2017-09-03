#include "Item.h"

const std::string & Item::getName() const
{
	return name;
}

const Vec2Tile & Item::getTile() const
{
	return position;
}

int Item::getAttack() const
{
	return attack;
}

int Item::getDefense() const
{
	return defense;
}

void Item::pick()
{
	picked = true;
}

bool Item::isPicked() const
{
	return picked;
}