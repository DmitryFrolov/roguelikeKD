#include "Fighter.h"

void Fighter::makeTurn(Warrior & warrior, std::shared_ptr<GameMap> gameMap)
{

	if (warrior.isDead())
		return;

	const int distance = positionTile.getDistance(warrior.getTilePosition());
	const Vec2Tile warriorPosition = warrior.getTilePosition();
	const bool nearby = (distance == 1);
	const bool canHit = (distance == 1) &&
		!((abs(warriorPosition.y - positionTile.y) == 1) && (abs(warriorPosition.x - positionTile.x) == 1));

	if (distance <= sightRadius) // if see
	{
		LOG("Fighter saw warrior");
		if (nearby)
		{
			LOG("Fighter nearby");
			if (canHit)
			{
				LOG("Fighter can hit");
				warrior.hit(getAttack());
				//renderer->animateSprite(*this, SA_ATTACK, false);
				//renderer->animateSprite(warrior, SA_HIT, false);

				if (warrior.isDead())
				{
					//renderer->removeSprite(warrior);
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
}

void Fighter::approachWarrior(const Vec2Tile & warriorPosition, std::shared_ptr<GameMap> gameMap)
{
	LOG("Fighter trying to approach");
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