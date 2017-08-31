#include "Item.h"

const std::string & Item::getName() const
{
	return name;
}

SpriteResource Item::getResource() const
{
	return spriteResource;
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

const Vec2Tile & Item::getPosition() const
{
	return position;
}
