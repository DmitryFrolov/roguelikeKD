#include "Ranger.h"

void Ranger::makeTurn(Warrior & warrior, std::shared_ptr<GameMap> gameMap)
{
	if (warrior.isDead())
		return;

	const int distance = positionTile.getDistance(warrior.getTilePosition());

	if ((distance <= sightRadius) && gameMap->getGameField().isPathOpen(positionTile, warrior.getTilePosition())) // if see
	{
		LOG("Ranger saw warrior");
		warrior.hit(getAttack());
		//pRenderer->animateSprite(*this, SA_ATTACK, false);
		//pRenderer->animateSprite(warrior, SA_HIT, false);

		if (warrior.isDead())
			Keeper::getInstance().end();

		// Based on ranger type chooshing projectile
		//pRenderer->createProjectile(position, warrior.getPosition(), Renderer::PT_ARROW);
	}
}
