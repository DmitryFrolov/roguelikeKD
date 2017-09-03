#include "Ranger.h"

void Ranger::makeTurn(std::shared_ptr<Warrior> warrior, std::shared_ptr<GameMap> gameMap)
{
	if (warrior->isDead() || this->isDead())
		return;

	const int distance = positionTile.getDistance(warrior->getTile());

	if ((distance <= sightRadius) && gameMap->getGameField().isPathOpen(positionTile, warrior->getTile())) // if see
	{
		LOG("%s saw and hit warrior\n", name.c_str());
		warrior->hit(getAttack());

		this->animate("attack", "idle");
		warrior->animate("onhit", "idle");

		if (warrior->isDead())
			return;

		// create an arrow
		// createWhizzbang(position, warrior->getPosition(), Renderer::PT_ARROW);
	}
}

void Ranger::initalizeAnimation()
{
	std::vector<SDL_Texture*> images;
	char str[256];
	for (int idx = 1; idx <= 5; idx++) {
		sprintf(str, "../Resources/Sprites/Vampire/idle%d.png", idx);
		images.push_back(Keeper::getInstance().getTextureManager()->getTexture(str));
	}
	addAnimation("idle", images);

	images.clear();
	images.push_back(Keeper::getInstance().getTextureManager()->getTexture("../Resources/Sprites/Vampire/attack1.png"));
	images.push_back(Keeper::getInstance().getTextureManager()->getTexture("../Resources/Sprites/Vampire/attack2.png"));
	addAnimation("attack", images);
}
