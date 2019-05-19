#include <Core/GlobalDefines.h>
#include <Managers/Keeper.h>

#include "Fighter.h"

void Fighter::makeTurn(std::shared_ptr<Warrior> warrior, std::shared_ptr<GameMap> gameMap)
{
	if (warrior->isDead() || this->isDead())
		return;

	const int distance = positionTile.getDistance(warrior->getTile());
	const Vec2Tile warriorPosition = warrior->getTile();
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
				this->animate("attack", "idle");
				warrior->animate("onhit", "idle");

				if (warrior->isDead())
				{
					positionTile = warriorPosition;
					return;
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

void Fighter::initalizeAnimation()
{
	std::vector<SDL_Texture*> images;
	char str[256];
	for (int idx = 1; idx <= 5; idx++) {
		sprintf(str, "../Resources/Sprites/Skeleton/idle%d.png", idx);
		images.push_back(Keeper::getInstance().getTextureManager()->getTexture(str));
	}
	addAnimation("idle", images);

	images.clear();
	images.push_back(Keeper::getInstance().getTextureManager()->getTexture("../Resources/Sprites/Skeleton/attack1.png"));
	images.push_back(Keeper::getInstance().getTextureManager()->getTexture("../Resources/Sprites/Skeleton/attack2.png"));
	addAnimation("attack", images);
}
