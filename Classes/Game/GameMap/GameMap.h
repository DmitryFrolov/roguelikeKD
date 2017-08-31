#ifndef GAME_MAP
#define GAME_MAP

#include <map>
#include "Objects/Node.h"
#include "Objects/Sprite.h"
#include "GameMap/GameField.h"

class GameMap : public Node
{
public:
	GameMap();
	virtual ~GameMap() {}
	static std::shared_ptr<GameMap> create();
	
	/*
		!!!Do not call multiple times!!!
		create all tiles on map
	*/
	void initalize();
	void fillFieldWithTiles(const Field & field);
	GameField getGameField();
	virtual void setPosition(Vec2 position) override;
	virtual void setPosition(float _x, float _y) override;
	Vec2 getTileCoordinates(Vec2Tile tile);
private:
	float findSpriteX(int index) const;
	float findSpriteY(int index) const;

	struct TileData
	{
		std::shared_ptr<Sprite> layer1;
		std::shared_ptr<Sprite> layer2;
	};
private:
	GameField gField;
	static const int tileSize = 32;
	TileData tileSprites[Field::FIELD_WIDTH][Field::FIELD_HEIGHT];
	std::shared_ptr<Node> layeringNode1;
	std::shared_ptr<Node> layeringNode2;
	std::map<TileResource, std::string> tileResources;
	//static std::map<SpriteResource, std::string> spriteResources;
};

#endif // !GAME_MAP
