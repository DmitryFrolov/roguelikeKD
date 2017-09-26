#include "GameMap.h"

GameMap::GameMap()
{
	setAnchorPoint(0, 0);

	layeringNode1 = Node::create();
	layeringNode2 = Node::create();

	tileResources[TileResource::TR_GROUND] = "../Resources/Sprites/Terrain/terrain1.png";
	tileResources[TileResource::TR_ROCK] = "../Resources/Sprites/Terrain/rock1.png";

	tileResources[TileResource::TR_BUSH1] = "../Resources/Sprites/Terrain/bush1.png";
	tileResources[TileResource::TR_BUSH2] = "../Resources/Sprites/Terrain/bush2.png";
	tileResources[TileResource::TR_BUSH3] = "../Resources/Sprites/Terrain/bush1.png";
	tileResources[TileResource::TR_BUSH4] = "../Resources/Sprites/Terrain/bush2.png";
	tileResources[TileResource::TR_BUSH5] = "../Resources/Sprites/Terrain/bush1.png";
	tileResources[TileResource::TR_BUSH6] = "../Resources/Sprites/Terrain/bush2.png";
}

std::shared_ptr<GameMap> GameMap::create()
{
	return std::make_shared<GameMap>();
}

void GameMap::initalize()
{
	this->addChild(layeringNode1, -1);
	this->addChild(layeringNode2, 0);

	gField = GameField();
	gField.reloadField();
	fillFieldWithTiles(gField);
}

GameField GameMap::getGameField()
{
	return gField;
}

void GameMap::setPosition(Vec2 position)
{
	setPosition(position.x, position.y);
}

void GameMap::setPosition(float _x, float _y)
{
	Vec2 oldPos = this->getPosition();
	layeringNode1->moveRecursive(_x - oldPos.x, _y - oldPos.y);
	layeringNode2->moveRecursive(_x - oldPos.x, _y - oldPos.y);
	Node::setPosition(_x, _y);
}

Vec2 GameMap::getTileCoordinates(Vec2Tile tile)
{
	return Vec2(findSpriteX(tile.x), findSpriteY(tile.y));
}

float GameMap::findSpriteX(int index) const
{
	return tileSize * index + getPositionX();
}

float GameMap::findSpriteY(int index) const
{
	return tileSize * index + getPositionY();
}

void GameMap::fillFieldWithTiles(const Field & field)
{
	for (int i = 0; i < Field::FIELD_WIDTH; i++)
	{
		for (int j = 0; j < Field::FIELD_HEIGHT; j++)
		{
			const TileResource layer1 = field.getLayer1TileResource(Vec2Tile(i, j));
			auto sprite1 = Sprite::create(tileResources[layer1]);
			tileSprites[i][j].layer1 = sprite1;
			sprite1->setPosition(findSpriteX(i), findSpriteY(j));
			layeringNode1->addChild(sprite1);

			const TileResource layer2 = field.getLayer2TileResource(Vec2Tile(i, j));
			if (layer2 == TileResource::TR_GROUND)
				continue;

			auto sprite2 = Sprite::create(tileResources[layer2]);
			tileSprites[i][j].layer2 = sprite2;
			sprite2->setPosition(findSpriteX(i), findSpriteY(j));
			layeringNode1->addChild(sprite2);
		}
	}
}