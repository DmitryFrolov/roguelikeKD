#ifndef GAME_MAP
#define GAME_MAP

#include "Objects/Node.h"
#include "Objects/Sprite.h"
#include "../Game/GameField.h"
#include <map>


class GameMap : public Node
{
public:
	GameMap();
	static std::shared_ptr<GameMap> create();
	void fillFieldWithTiles(const Field & field);

	/*
		!!!Do not call multiple times!!!
		create all tiles on map
	*/
	void initalize();

	void resetField();
private:
	float findSpriteX(int index) const;
	float findSpriteY(int index) const;

	struct TileData
	{
		std::shared_ptr<Sprite> layer1;
		std::shared_ptr<Sprite> layer2;
	};
private:
	static const int tileSize = 32;
	TileData tileSprites[Field::FIELD_WIDTH][Field::FIELD_HEIGHT];
	std::shared_ptr<Node> layeringNode1;
	std::shared_ptr<Node> layeringNode2;
	std::map<TileResource, std::string> tileResources;
	//static std::map<SpriteResource, std::string> spriteResources;

};

#endif // !GAME_MAP
