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
	auto gameMap = GameMap::create();
	gameMap->initalize();
	gameMap->setPosition(20, 20);
	gameMap->resetField();
	this->addChild(gameMap);

	return true;
}
