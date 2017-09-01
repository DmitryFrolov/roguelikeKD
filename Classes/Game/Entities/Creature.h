#ifndef CREATURE
#define CREATURE

#include <string>
#include "Objects/Sprite.h"
#include "GameMap/GameMap.h"
#include "Entities/Entity.h"

class Warrior;
class GameMap;

class Creature : public Entity, public Sprite
{
protected:
	SpriteResource spriteResource;
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
	bool isDead() const; 
	void moveTo(const Vec2Tile & where);
	
	virtual int getAttack() const;
	virtual int getDefense() const;

	virtual int getExperience() const;
	virtual const Vec2Tile & getTilePosition() const;
	

private:
	virtual const std::string & getName() const override;
	virtual SpriteResource getResource() const override;
	virtual const Vec2Tile & getTile() const override;

public:
	Creature() {}
	Creature(
		const std::string imgPath,
		const SpriteResource & _spriteResource,
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
