#ifndef CREATURE
#define CREATURE

#include <string>
#include "Objects/AnimatedSprite.h"
#include "GameMap/GameMap.h"
#include "GameMap/Field.h"

class Warrior;
class GameMap;

class Creature : public AnimatedSprite
{
protected:
	Vec2Tile positionTile;
	std::string name;
 
	int sightRadius;
	int experience;
	int defense;
	int attack;
	int hits;

public:
	virtual void makeTurn(std::shared_ptr<Warrior> warrior, std::shared_ptr<GameMap> gameMap)
	{
		/* Enemies only */ 
	}

	void hit(int enemyAttack);
	void moveTo(const Vec2Tile & where);

	bool isDead() const;
	virtual int getAttack() const;
	virtual int getDefense() const;
	virtual int getExperience() const;
	virtual const Vec2Tile & getTile() const;
private:
	virtual const std::string & getName() const;

public:
	Creature() {}
	Creature(
		const Vec2Tile & positionTile,
		const std::string & _name,
		int _sightRadius,
		int _experience,
		int _defense, 
		int _attack,
		int _hits);

	virtual ~Creature() {}
};

#endif // !CREATURE
