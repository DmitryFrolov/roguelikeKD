#ifndef RANGER
#define RANGER

#include "GameMap/GameMap.h"
#include "Entities/Creature.h"
#include "Entities/Warrior.h"

class Ranger : public Creature
{
public:
	Ranger(
		const Vec2Tile & _position,
		const std::string & _name,
		int _sightRadius,
		int _experience,
		int _defense,
		int _attack,
		int _hits)
		: Creature(_position, _name, _sightRadius, _experience, _defense, _attack, _hits)
	{
		initalizeAnimation();
	}

	virtual void makeTurn(std::shared_ptr<Warrior> warrior, std::shared_ptr<GameMap> gameMap);

private:
	void initalizeAnimation();
};

#endif // !RANGER
