#include "Creature.h"

Creature::Creature(
	const std::string imgPath,
	const SpriteResource & _spriteResource,
	const Vec2Tile & _position,
	const std::string & _name,
	int _sightRadius,
	int _experience,
	int _defense,
	int _attack,
	int _hits)

	: Sprite(imgPath)
	, spriteResource(_spriteResource)
	, positionTile(_position)
	, name(_name)
	, sightRadius(_sightRadius)
	, experience(_experience)
	, defense(_defense)
	, attack(_attack)
	, hits(_hits)
{
	assert(name.size() > 0);
	assert(hits > 0);
	assert(attack > 0);
	assert(defense > 0);
	assert(sightRadius >= 0);
	assert(experience >= 0);
}

void Creature::hit(int enemyAttack)
{
	int damage = (int)enemyAttack / defense;
	hits = hits - damage;
	LOG("%s get $i damage\n", name, damage);
}

bool Creature::isDead() const
{
	return hits <= 0; 
}

void Creature::moveTo(const Vec2Tile & moveTo)
{
	positionTile = moveTo;
}

int Creature::getAttack() const
{
	return attack;
}

int Creature::getDefense() const
{
	return defense;
}

int Creature::getExperience() const
{
	return experience;
}

const Vec2Tile & Creature::getTilePosition() const
{
	return positionTile;
}

const std::string & Creature::getName() const 
{
	return name; 
}

SpriteResource Creature::getResource() const 
{
	return spriteResource; 
}

const Vec2Tile & Creature::getTile() const  //TODO: rm
{ 
	return positionTile;
}
