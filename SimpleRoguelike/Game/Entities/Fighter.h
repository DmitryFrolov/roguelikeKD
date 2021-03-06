#ifndef FIGHTER
#define FIGHTER

#include "Entities/Creature.h"
#include "GameMap/GameMap.h"
#include "Entities/Warrior.h"

class Fighter : public Creature
{
public:
	Fighter(
		const Vec2Tile & _position,
		const std::string & _name,
		int _sightRadius,
		int _experience,
		int _defense,
		int _attack,
		int _hits)
		: Creature (_position, _name, _sightRadius, _experience, _defense, _attack, _hits)
	{
		initalizeAnimation();
	}

	virtual void makeTurn(std::shared_ptr<Warrior> warrior, std::shared_ptr<GameMap> gameMap);

private:
	void approachWarrior(const Vec2Tile & warriorPosition, std::shared_ptr<GameMap> gameMap);
	void initalizeAnimation();
};

#endif //FIGHTER
