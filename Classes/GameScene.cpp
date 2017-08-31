#include "GameScene.h"

std::shared_ptr<GameScene> GameScene::create()
{
	auto pRet = std::make_shared<GameScene>();
	if (pRet)
		if( pRet->init())
		return pRet;
	else
		assert(false);
}

bool GameScene::init()
{
	// game map creation
	gMap = GameMap::create();
	gMap->setPosition(16, 16);
	gMap->initalize();
	this->addChild(gMap);
	
	// warrior creation
	warrior = std::make_shared<Warrior>("../Resources/Sprites/BeardMan/idle1.png", 
		SpriteResource::SR_WARRIOR, g_warriorPos, 0, 0, 
		WARRIOR_DEFENSE_1, WARRIOR_ATTACK_1, WARRIOR_HITS_1);
	warrior->setPosition(gMap->getTileCoordinates(g_warriorPos));
	gMap->addChild(warrior);

	KeyboardEventHolder moveWarrior = KeyboardEventHolder();
	moveWarrior.onKeyPressed([this](SDL_KeyboardEvent *key, float dt) 
	{
		if (warrior->isDead())
			return;

		auto kbButton = key->keysym.sym;
		Vec2Tile newPos = warrior->getTilePosition();

		if (kbButton == SDLK_w || kbButton == SDLK_UP) {
			newPos.y = newPos.y - 1;
			OKP(newPos);
		}
		else if (kbButton == SDLK_a || kbButton == SDLK_LEFT) {
			newPos.x = newPos.x - 1;
			OKP(newPos);
		}
		else if (kbButton == SDLK_s || kbButton == SDLK_DOWN) {
			newPos.y = newPos.y + 1;
			OKP(newPos);
		}
		else if (kbButton == SDLK_d || kbButton == SDLK_RIGHT) {
			newPos.x = newPos.x + 1;
			OKP(newPos);
		}		
	});

	// enemies creation

	eventHandler.addKeyboardHolder(moveWarrior);
	return true;
}

std::shared_ptr<Creature> GameScene::findVictim(const Vec2Tile tile)
{
	for (auto creature : creatures)	{
		if (creature->getTilePosition() == tile)
			return creature;
	}
	return nullptr;
}

void GameScene::OKP(Vec2Tile targetPosition)
{
	if (gMap->getGameField().isTileOpen(targetPosition)) {
		if (std::shared_ptr<Creature> victim = findVictim(targetPosition)) {
			if (!victim->isDead()) { // If victim is still alive
				victim->hit(warrior->getAttack());
				//animateSprite(warrior, SA_ATTACK, false);
				//animateSprite(*victim, SA_HIT, false);
				if (victim->isDead()) {
					// If after hit victim is dead
					//createBlood(targetPosition);
					warrior->gainExperience(victim->getExperience());
					//removeSprite(victim);
					warrior->moveTo(targetPosition);
					warrior->setPosition(gMap->getTileCoordinates(targetPosition));
					//animateSprite(warrior, SA_IDLE, false);
				}
			}
			else {
				warrior->moveTo(targetPosition);
				warrior->setPosition(gMap->getTileCoordinates(targetPosition));
				//animateSprite(warrior, SA_IDLE, false);
			}
		}
		else {
			warrior->moveTo(targetPosition);
			warrior->setPosition(gMap->getTileCoordinates(targetPosition));
			//animateSprite(warrior, SA_IDLE, false);
		}
	}
	LOG("warrior tile position = (%i,%i) \n", targetPosition.x, targetPosition.y);
}
