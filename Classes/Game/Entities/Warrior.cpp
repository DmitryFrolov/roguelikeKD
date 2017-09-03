#include "Warrior.h"

void Warrior::gainExperience(int exp)
{
	experience += exp;

	switch (level)
	{
	case 1:
		if (experience >= WARRIOR_EXP_TO_2)
		{
			level++;
			maxHits = WARRIOR_HITS_2;
			hits = WARRIOR_HITS_2;
			attack = WARRIOR_ATTACK_2;
			defense = WARRIOR_DEFENSE_2;
			nextLevel = WARRIOR_EXP_TO_3;
		}
		break;

	case 2:
		if (experience >= WARRIOR_EXP_TO_3)
		{
			level++;
			maxHits = WARRIOR_HITS_3;
			hits = WARRIOR_HITS_3;
			attack = WARRIOR_ATTACK_3;
			defense = WARRIOR_DEFENSE_3;
			nextLevel = WARRIOR_EXP_TO_4;
		}
		break;

	case 3:
		if (experience >= WARRIOR_EXP_TO_4)
		{
			level++;
			maxHits = WARRIOR_HITS_4;
			hits = WARRIOR_HITS_4;
			attack = WARRIOR_ATTACK_4;
			defense = WARRIOR_DEFENSE_4;
			nextLevel = WARRIOR_EXP_TO_4;
		}
		break;
	}
	LOG("warriors exp = %i ", experience);
	LOG("warriors lvl = %i\n", level);
}

void Warrior::upgrade(std::shared_ptr<Item> item)
{
	attackBoost += item->getAttack();
	defenseBoost += item->getDefense();
}

int Warrior::getCurrentHits() const
{
	return hits;
}

int Warrior::getMaxHits() const
{
	return maxHits;
}

int Warrior::getNextLevelExp() const
{
	return nextLevel;
}

int Warrior::getCurrentLevel() const
{
	return level;
}

int Warrior::getAttack() const
{
	return attack + attackBoost;
}

int Warrior::getDefense() const
{
	return defense + defenseBoost;
}

void Warrior::initalizeAnimation()
{
	std::vector<SDL_Texture*> images;
	char str[256];
	for (int idx = 1; idx <= 5; idx++) {
		sprintf(str, "../Resources/Sprites/BeardMan/idle%d.png", idx);
		images.push_back(Keeper::getInstance().getTextureManager()->getTexture(str));
	}
	addAnimation("idle", images);
	
	images.clear();
	images.push_back(Keeper::getInstance().getTextureManager()->getTexture("../Resources/Sprites/BeardMan/attack1.png"));
	images.push_back(Keeper::getInstance().getTextureManager()->getTexture("../Resources/Sprites/BeardMan/attack2.png"));
	addAnimation("attack", images);

	images.clear();
	images.push_back(Keeper::getInstance().getTextureManager()->getTexture("../Resources/Sprites/BeardMan/onhit1.png"));
	images.push_back(Keeper::getInstance().getTextureManager()->getTexture("../Resources/Sprites/BeardMan/onhit2.png"));
	addAnimation("onhit", images);
}
