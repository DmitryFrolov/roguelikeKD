#include "Game.h"
#include "GameScene.h"

int main(int argc, char** argv)
{
	Game* game = new Game();
	Keeper::getInstance().runFirstScene(GameScene::create());
	game->run(); 
	return 0;
}
