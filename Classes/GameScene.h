#pragma once
#ifndef __INITIAL_SCENE_H__
#define __INITIAL_SCENE_H__ 

#include <vector>
#include "Objects/Scene.h"
#include "GameMap/GameMap.h"
#include "Entities/Warrior.h"

class GameScene : public Scene
{
private:
	std::shared_ptr<GameMap> gMap;
	std::shared_ptr<Warrior> warrior;
	std::vector<std::shared_ptr<Creature>> creatures;
private:
	virtual bool init();
	void OKP(Vec2Tile np);
	std::shared_ptr<Creature> findVictim(const Vec2Tile tile);
public:
	static std::shared_ptr<GameScene> create();
};

#endif // !__INITIAL_SCENE_H__
