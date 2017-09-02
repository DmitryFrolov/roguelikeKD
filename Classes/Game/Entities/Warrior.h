#ifndef WARRIOR
#define WARRIOR

#include "Entities/Creature.h"
#include "Entities/Item.h"
#include "Entities/Stats.h"

class Warrior : public Creature
{
private:
	int level;
	int maxHits;
	int nextLevel;

	int attackBoost;
	int defenseBoost;

public:
	enum class MoveType
	{
		MV_LEFT,
		MV_RIGHT, 
		MV_UP,
		MV_DOWN
	};
	Warrior() {}
	Warrior(
		const SpriteResource & _spriteResource,
		const Vec2Tile & positionTile,
		int _sightRadius,
		int _experience,
		int _defense,
		int _attack,
		int _hits)
		: Creature(_spriteResource, positionTile, "Warrior", _sightRadius, _experience, _defense, _attack, _hits)
	{
		assert(_hits > 0);

		level = 1;
		maxHits = _hits;
		nextLevel = WARRIOR_EXP_TO_2;

		attackBoost = 0;
		defenseBoost = 0;
		initalizeAnimation();
	}
	void gainExperience(int exp);
	void upgrade(Item item);

public:
	int getCurrentHits() const;
	int getMaxHits() const;
	int getNextLevelExp() const;
	int getCurrentLevel() const;
	virtual int getAttack() const;
	virtual int getDefense() const;

private: 
	void initalizeAnimation();
};

#endif // !WARRIOR
