#pragma once
#ifndef __INITIAL_SCENE_H__
#define __INITIAL_SCENE_H__ 

#include <vector>
#include "Objects/Scene.h"
#include "GameMap/GameMap.h"
#include "Entities/Warrior.h"
#include "Entities/Ranger.h"
#include "Entities/Fighter.h"

#include "Objects/AnimatedSprite.h"


class GameScene : public Scene
{
private:
	struct EnemiesCounter
	{
		int fighter1Count;
		int fighter2Count;
		int ranger1Count;
		int ranger2Count;
		EnemiesCounter()
			: fighter1Count(0)
			, fighter2Count(0)
			, ranger1Count(0)
			, ranger2Count(0)
		{}
	};
	EnemiesCounter counter;
	std::shared_ptr<GameMap> gMap;
	std::shared_ptr<Warrior> warrior;
	std::vector<std::shared_ptr<Creature>> creatures;
	std::vector<std::shared_ptr<Item>> items;
private:
	virtual bool init();
	void createWarrior();
	void createEnemies();
	void createBlood(Vec2Tile targetPosition);
	void processWarriorsTurn(Vec2Tile np);
	void pickupItem();
	void enemiesTurn();
	std::shared_ptr<Creature> findVictim(const Vec2Tile tile);

	void gameOver();
public:
	static std::shared_ptr<GameScene> create();
};

#endif // !__INITIAL_SCENE_H__
