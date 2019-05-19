#include "Game.h"
#include "GameScene.h"

int main(int argc, char** argv)
{
	Keeper::applySettings(EngineSettings("config.json"));
	Game game = Game();
	Keeper::getInstance().runFirstScene(GameScene::create());
	game.run();
	return 0;
}
