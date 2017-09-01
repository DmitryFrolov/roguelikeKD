#include "Fighter.h"

void Fighter::makeTurn(std::shared_ptr<Warrior> warrior, std::shared_ptr<GameMap> gameMap)
{
	if (warrior->isDead() || this->isDead())
		return;

	const int distance = positionTile.getDistance(warrior->getTilePosition());
	const Vec2Tile warriorPosition = warrior->getTilePosition();
	const bool nearby = (distance == 1);
	const bool canHit = nearby &&
		!((abs(warriorPosition.y - positionTile.y) == 1) && (abs(warriorPosition.x - positionTile.x) == 1));

	if (distance <= sightRadius) // if see
	{
		LOG("%s saw warrior ", name.c_str());
		if (nearby)
		{
			LOG("& nearby ");
			if (canHit)
			{
				LOG("& can hit ");
				warrior->hit(getAttack());
				//animateSprite(*this, SA_ATTACK, false);
				//animateSprite(warrior, SA_HIT, false);

				if (warrior->isDead())
				{
					positionTile = warriorPosition;
					Keeper::getInstance().end();
				}
			}
			else
			{
				approachWarrior(warriorPosition, gameMap);
			}
		}
		else
		{
			approachWarrior(warriorPosition, gameMap);
		}
	}
	LOG('\n');
}

void Fighter::approachWarrior(const Vec2Tile & warriorPosition, std::shared_ptr<GameMap> gameMap)
{
	LOG("%s trying to approach\n", name.c_str());
	Vec2Tile where = positionTile;

	int deltaX = warriorPosition.x - positionTile.x;
	int deltaY = warriorPosition.y - positionTile.y;

	if (abs(deltaX) > abs(deltaY))
	{
		if (deltaX > 0)
		where.x += 1;
		else
		where.x -= 1;
	}
	else
	{
		if (deltaY > 0)
		where.y += 1;
		else
		where.y -= 1;
	}

	if (gameMap->getGameField().isTileOpen(where)) {
		positionTile = where;
		setPosition(gameMap->getTileCoordinates(positionTile));
	}
}