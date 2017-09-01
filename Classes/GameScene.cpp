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
			gameOver();

		auto kbButton = key->keysym.sym;
		Vec2Tile newPos = warrior->getTilePosition();

		if (kbButton == SDLK_w || kbButton == SDLK_UP) {
			newPos.y = newPos.y - 1;
			OKP(newPos);
			enemiesTurn();
		}
		else if (kbButton == SDLK_a || kbButton == SDLK_LEFT) {
			newPos.x = newPos.x - 1;
			OKP(newPos);
			enemiesTurn();
		}
		else if (kbButton == SDLK_s || kbButton == SDLK_DOWN) {
			newPos.y = newPos.y + 1;
			OKP(newPos);
			enemiesTurn();
		}
		else if (kbButton == SDLK_d || kbButton == SDLK_RIGHT) {
			newPos.x = newPos.x + 1;
			OKP(newPos);
			enemiesTurn();
		}

		if (kbButton == SDLK_TAB){
			LOG("Hits - %i\n", warrior->getCurrentHits());
		}
		if (warrior->isDead())
			gameOver();
	});

	// enemies creation
	createEnemies();
	eventHandler.addKeyboardHolder(moveWarrior);
	return true;
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
					
					//remove enemy
					victim->removeFromParent();
					//creatures.erase(std::find(creatures.begin(), creatures.end(), victim));
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

std::shared_ptr<Creature> GameScene::findVictim(const Vec2Tile tile)
{
	for (auto creature : creatures) {
		if (creature->getTilePosition() == tile)
			return creature;
	}
	return nullptr;
}

void GameScene::gameOver()
{
	Keeper::getInstance().end();
}

void GameScene::createEnemies()
{
	counter = EnemiesCounter();
	creatures.clear();

	for (int j = 0; j < Field::FIELD_HEIGHT; j++)
	{
		for (int i = 0; i < Field::FIELD_WIDTH; i++)
		{
			const int entity = g_entities[i + j * Field::FIELD_WIDTH];

			switch (entity)
			{
			case 0:
				// empty
				break;

			case SR_SKELETON1:
			{
				counter.fighter1Count++;
				auto fighter1 = std::make_shared<Fighter>(
					"../Resources/Sprites/Skeleton/idle1.png",
					SR_SKELETON1,
					Vec2Tile(i, j),
					"SSkeleton" + std::to_string(counter.fighter1Count),
					FIGHTER1_SIGHT_RADIUS,
					FIGHTER1_EXPERIENCE,
					FIGHTER1_DEFENSE,
					FIGHTER1_ATTACK,
					FIGHTER1_HITS);
				creatures.push_back(fighter1);
				fighter1->setPosition(gMap->getTileCoordinates(Vec2Tile(i, j)));
			}
			break;

			case SR_VAMPIRE1:
			{
				counter.ranger1Count++;
				auto ranger1 = std::make_shared<Ranger>(
					"../Resources/Sprites/Vampire/idle1.png",
					SR_VAMPIRE1,
					Vec2Tile(i, j), 
					"SVampire" + std::to_string(counter.ranger1Count),
					RANGER1_SIGHT_RADIUS,
					RANGER1_EXPERIENCE,
					RANGER1_DEFENSE,
					RANGER1_ATTACK,
					RANGER1_HITS);
				creatures.push_back(ranger1);
				ranger1->setPosition(gMap->getTileCoordinates(Vec2Tile(i, j)));
			}
			break;

			case SR_SKELETON2:
			{
				counter.fighter2Count++;
				auto fighter2 = std::make_shared<Fighter>(
					"../Resources/Sprites/Skeleton/idle1.png",
					SR_SKELETON2,
					Vec2Tile(i, j), 
					"BSkeleton" + std::to_string(counter.fighter2Count),
					FIGHTER2_SIGHT_RADIUS,
					FIGHTER2_EXPERIENCE,
					FIGHTER2_DEFENSE,
					FIGHTER2_ATTACK,
					FIGHTER2_HITS);
				creatures.push_back(fighter2);
				fighter2->setPosition(gMap->getTileCoordinates(Vec2Tile(i, j)));
				fighter2->setScale(1.5);
			}
			break;

			case SR_VAMPIRE2:
			{
				counter.ranger2Count++;
				auto ranger2 = std::make_shared<Ranger>(
					"../Resources/Sprites/Vampire/idle1.png",
					SR_VAMPIRE2,
					Vec2Tile(i, j),
					"BVampire" + std::to_string(counter.ranger2Count),
					RANGER2_SIGHT_RADIUS,
					RANGER2_EXPERIENCE,
					RANGER2_DEFENSE,
					RANGER2_ATTACK,
					RANGER2_HITS);
				creatures.push_back(ranger2);
				ranger2->setPosition(gMap->getTileCoordinates(Vec2Tile(i, j)));
				ranger2->setScale(1.5);
			}
			break;

			case SR_ITEM1:
				//sword = Item("Sword", SR_SWORD, Vec2(i, j), SWORD_ATTACK, SWORD_DEFENSE);
				break;

			case SR_ITEM2:
				//shield = Item("Shield", SR_SHIELD, Vec2(i, j), SHIELD_ATTACK, SHIELD_DEFENSE);
				break;

			case SR_ITEM3:
				//cuirass = Item("Cuirass", SR_CUIRASS, Vec2(i, j), CUIRASS_ATTACK, CUIRASS_DEFENSE);
				break;

			default:
				assert(false);
				break;
			}
		}
	}

	for(auto creature : creatures){
		this->addChild(creature);
	}
}

void GameScene::enemiesTurn()
{
	for (auto enemy : creatures)
		enemy->makeTurn(warrior, gMap);
}

