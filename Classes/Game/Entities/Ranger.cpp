#include "Ranger.h"

void Ranger::makeTurn(std::shared_ptr<Warrior> warrior, std::shared_ptr<GameMap> gameMap)
{
	
	if (warrior->isDead() || this->isDead())
		return;

	const int distance = positionTile.getDistance(warrior->getTilePosition());

	if ((distance <= sightRadius) && gameMap->getGameField().isPathOpen(positionTile, warrior->getTilePosition())) // if see
	{
		LOG("%s saw and hit warrior\n", name.c_str());
		warrior->hit(getAttack());
		//pRenderer->animateSprite(*this, SA_ATTACK, false);
		//pRenderer->animateSprite(warrior, SA_HIT, false);

		if (warrior->isDead())
			return;

		// Based on ranger type chooshing projectile
		//pRenderer->createProjectile(position, warrior.getPosition(), Renderer::PT_ARROW);
	}
}
