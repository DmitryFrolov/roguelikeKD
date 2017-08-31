#include "GameField.h"
//-------------------------------------------------------------------------------------

void GameField::reloadField()
{
	for (int j = 0; j < Field::FIELD_HEIGHT; j++)
	{
		for (int i = 0; i < Field::FIELD_WIDTH; i++)
		{
			TileData & data = getTileAt(Vec2Tile(i, j));
			data.layer1 = TileResource(g_layer1[i + j * Field::FIELD_WIDTH]);
			data.layer2 = TileResource(g_layer2[i + j * Field::FIELD_WIDTH]);
		}
	}
}

//-------------------------------------------------------------------------------------

bool GameField::isTileOpen(const Vec2Tile & tile) const
{
	if (tile.x < 0 || tile.x >= Field::FIELD_WIDTH || tile.y < 0 || tile.y >= Field::FIELD_HEIGHT)
		return false;

	return getTileAt(tile).isOpen();
}

//-------------------------------------------------------------------------------------

bool GameField::isPathOpen(const Vec2Tile & from, const Vec2Tile & to) const
{
	int l, dx, dy;
	int xr = abs(to.x - from.x);
	int yr = abs(to.y - from.y);

	if (xr > yr)
	{
		l = xr;
	}
	else
	{
		l = yr;
	}

	int px = (from.x << 12) + (1 << 11);
	int py = (from.y << 12) + (1 << 11);
	int ex = (to.x << 12) + (1 << 11);
	int ey = (to.y << 12) + (1 << 11);

	if (l != 0)
	{
		dx = (ex - px) / l;
		dy = (ey - py) / l;
	}
	else
	{
		dx = 0;
		dy = 0;
	}

	for (int i = 0; i <= l; i++)
	{
		if (!getTileAt(Vec2Tile(px >> 12, py >> 12)).isOpen())
			return false;

		px += dx;
		py += dy;
	}

	return true;
}

TileResource GameField::getLayer1TileResource(const Vec2Tile & tile) const
{
	return getTileAt(tile).layer1;
}

TileResource GameField::getLayer2TileResource(const Vec2Tile & tile) const
{
	return getTileAt(tile).layer2;
}

GameField::TileData & GameField::getTileAt(const Vec2Tile & tile)
{
	assert(tile.x >= 0 && tile.x < Field::FIELD_WIDTH);
	assert(tile.y >= 0 && tile.y < Field::FIELD_HEIGHT);

	return field[tile.x][tile.y];
}

const GameField::TileData & GameField::getTileAt(const Vec2Tile & tile) const
{
	assert(tile.x >= 0 && tile.x < Field::FIELD_WIDTH);
	assert(tile.y >= 0 && tile.y < Field::FIELD_HEIGHT);

	return field[tile.x][tile.y];
}
