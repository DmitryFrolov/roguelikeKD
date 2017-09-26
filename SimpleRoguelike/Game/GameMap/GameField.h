#ifndef GAME_FIELD
#define GAME_FIELD

#include "Field.h"
#include "Map.h"


class GameField : public Field
{
public:
	void reloadField();
	bool isTileOpen(const Vec2Tile & tile) const;
	bool isPathOpen(const Vec2Tile & from, const Vec2Tile & to) const;

private:
	virtual TileResource getLayer1TileResource(const Vec2Tile & tile) const;
	virtual TileResource getLayer2TileResource(const Vec2Tile & tile) const;

private:
	struct TileData
	{
		TileResource layer1;
		TileResource layer2;

		bool isOpen() const
		{
			return layer1 == TileResource::TR_GROUND &&
				((layer2 != TileResource::TR_BUSH1) && (layer2 != TileResource::TR_BUSH2) &&
				(layer2 != TileResource::TR_BUSH3) && (layer2 != TileResource::TR_BUSH4) && 
				(layer2 != TileResource::TR_BUSH5) && (layer2 != TileResource::TR_BUSH6));
		}
	};

	TileData field[Field::FIELD_WIDTH][Field::FIELD_HEIGHT];

	TileData & getTileAt(const Vec2Tile & tile);
	const TileData & getTileAt(const Vec2Tile & tile) const;
};

#endif // !GAME_FIELD
