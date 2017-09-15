#include "GameScene.h"

std::shared_ptr<GameScene> GameScene::create()
{
	auto pRet = std::make_shared<GameScene>();
	if (pRet)
		if(pRet->init())
			return pRet;
	else
		assert(false);
}

bool GameScene::init()
{
	// game map creation
	gMap = GameMap::create();
	gMap->setPosition(16, 16); //tileSize / 2
	gMap->initalize();
	
	createWarrior();
	createEnemies();

	auto warriorStats = std::make_shared<CurrentStats>(warrior);
	warriorStats->setPosition(1366 - 150, 70);

	this->addChild(warriorStats);
	this->addChild(gMap, -1);
	
	/*setup camera*/
	Keeper::getInstance().getCamera()->setTargetNode(warrior);
	Keeper::getInstance().getCamera()->setCameraBounds(0, 1366, 0, 800);
	return true;
}

void GameScene::createWarrior()
{
	warrior = std::make_shared<Warrior>(
		g_warriorPos, 0, 0, 
		WARRIOR_DEFENSE_1,
		WARRIOR_ATTACK_1, 
		WARRIOR_HITS_1);
	warrior->setPosition(gMap->getTileCoordinates(g_warriorPos));
	warrior->animateLooped("idle");
	this->addChild(warrior, 1);


	KeyboardEventHolder moveWarrior = KeyboardEventHolder();
	moveWarrior.onKeyPressed([this](SDL_KeyboardEvent *key, float dt)
	{
		if (warrior->isDead())
			gameOver();

		auto kbButton = key->keysym.sym;
		Vec2Tile newPos = warrior->getTile();

		if (kbButton == SDLK_w || kbButton == SDLK_UP) {
			newPos.y = newPos.y - 1;
			processWarriorsTurn(newPos);
			enemiesTurn();
		}
		else if (kbButton == SDLK_a || kbButton == SDLK_LEFT) {
			newPos.x = newPos.x - 1;
			processWarriorsTurn(newPos);
			enemiesTurn();
		}
		else if (kbButton == SDLK_s || kbButton == SDLK_DOWN) {
			newPos.y = newPos.y + 1;
			processWarriorsTurn(newPos);
			enemiesTurn();
		}
		else if (kbButton == SDLK_d || kbButton == SDLK_RIGHT) {
			newPos.x = newPos.x + 1;
			processWarriorsTurn(newPos);
			enemiesTurn();
		}
		else if (kbButton == SDLK_SPACE) {
			pickupItem();
			enemiesTurn();
		}

		if (warrior->isDead())
			gameOver();
	});
	eventHandler.addKeyboardHolder(moveWarrior);
}

void GameScene::processWarriorsTurn(Vec2Tile targetPosition)
{
	if (gMap->getGameField().isTileOpen(targetPosition)) {
		if (std::shared_ptr<Creature> victim = findVictim(targetPosition)) {
			if (!victim->isDead()) { 
				// If victim is still alive
				victim->hit(warrior->getAttack());
				warrior->animate("attack", "idle");

				if (victim->isDead()) {
					// If after hit victim is dead
					createBlood(targetPosition);
					warrior->gainExperience(victim->getExperience());
					warrior->moveTo(targetPosition);
					warrior->setPosition(gMap->getTileCoordinates(targetPosition));
					
					//remove enemy
					victim->removeFromParent();
				}
			}
			else {
				warrior->moveTo(targetPosition);
				warrior->setPosition(gMap->getTileCoordinates(targetPosition));
			}
		}
		else {
			warrior->moveTo(targetPosition);
			warrior->setPosition(gMap->getTileCoordinates(targetPosition));
		}
	}
}

void GameScene::pickupItem()
{
	auto it = std::find_if(items.begin(), items.end(), [this](std::shared_ptr<Item> item) {
		return item->getTile() == warrior->getTile();
	});

	if (it != items.end())
	{
		warrior->upgrade(*it);
		this->removeChild(*it);
		(*it)->pick();
		items.erase(it);
	}
}


std::shared_ptr<Creature> GameScene::findVictim(const Vec2Tile tile)
{
	for (auto creature : creatures) {
		if (creature->getTile() == tile)
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

			case SR_SKELETON:
			{
				counter.fighter1Count++;
				auto fighter1 = std::make_shared<Fighter>(
					Vec2Tile(i, j),
					"SSkeleton" + std::to_string(counter.fighter1Count),
					FIGHTER1_SIGHT_RADIUS,
					FIGHTER1_EXPERIENCE,
					FIGHTER1_DEFENSE,
					FIGHTER1_ATTACK,
					FIGHTER1_HITS);
				creatures.push_back(fighter1);
				fighter1->setPosition(gMap->getTileCoordinates(Vec2Tile(i, j)));
				fighter1->animateLooped("idle");
				break;
			}

			case SR_VAMPIRE:
			{
				counter.ranger1Count++;
				auto ranger1 = std::make_shared<Ranger>(
					Vec2Tile(i, j),
					"SVampire" + std::to_string(counter.ranger1Count),
					RANGER1_SIGHT_RADIUS,
					RANGER1_EXPERIENCE,
					RANGER1_DEFENSE,
					RANGER1_ATTACK,
					RANGER1_HITS);
				creatures.push_back(ranger1);
				ranger1->setPosition(gMap->getTileCoordinates(Vec2Tile(i, j)));
				ranger1->animateLooped("idle");
				break;
			}

			case SR_BIG_SKELETON:
			{
				counter.fighter2Count++;
				auto fighter2 = std::make_shared<Fighter>(
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
				fighter2->animateLooped("idle");
				break;
			}

			case SR_BIG_VAMPIRE:
			{
				counter.ranger2Count++;
				auto ranger2 = std::make_shared<Ranger>(
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
				ranger2->animateLooped("idle");
				break;
			}

			case SR_ITEM1:
			{
				auto sword = std::make_shared<Item>("../Resources/Sprites/Items/sword.png", Vec2Tile(i, j), "Sword", SWORD_DEFENSE, SWORD_ATTACK);
				sword->setPosition(gMap->getTileCoordinates(Vec2Tile(i, j)));
				items.push_back(sword);
				break;
			}

			case SR_ITEM2:
			{
				auto shield = std::make_shared<Item>("../Resources/Sprites/Items/shield.png", Vec2Tile(i, j), "Shield", SHIELD_DEFENSE, SHIELD_ATTACK);
				shield->setPosition(gMap->getTileCoordinates(Vec2Tile(i, j)));
				items.push_back(shield);
				break;
			}

			case SR_ITEM3:
			{
				auto helmet = std::make_shared<Item>("../Resources/Sprites/Items/helmet.png", Vec2Tile(i, j), "Cuirass", CUIRASS_DEFENSE, CUIRASS_ATTACK);
				helmet->setPosition(gMap->getTileCoordinates(Vec2Tile(i, j)));
				items.push_back(helmet);
				break;
			}

			default:
				assert(false);
				break;
			}
		}
	}
	
	for (auto creature : creatures)
		this->addChild(creature, 1);

	for (auto item : items)
		this->addChild(item);
}

void GameScene::createBlood(Vec2Tile targetPosition)
{
	auto blood = Sprite::create("../Resources/Sprites/Items/blood.png");
	blood->setPosition(gMap->getTileCoordinates(targetPosition));
	this->addChild(blood);
}

void GameScene::enemiesTurn()
{
	for (auto enemy : creatures)
		enemy->makeTurn(warrior, gMap);
}
