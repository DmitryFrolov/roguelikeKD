#pragma once
#ifndef __INITIAL_SCENE_H__
#define __INITIAL_SCENE_H__ 

#include "Objects/Scene.h"
#include "../Game/GameMap.h"

class GameScene : public Scene
{
public:
	static std::shared_ptr<GameScene> create();
private:
	virtual bool init();
};

#endif // !__INITIAL_SCENE_H__
