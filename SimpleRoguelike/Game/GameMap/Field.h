#ifndef FIELD
#define FIELD

#include <assert.h>
#include <math.h>
#include "Core/Vec2.h"

/*
	Integer version of Vec2 to describe tile positions 
*/
struct Vec2Tile
{
	int x;
	int y;

public:
	Vec2Tile() :x(0), y(0) {}
	Vec2Tile(int _x, int _y) :x(_x), y(_y) {}

	bool operator== (const Vec2Tile & other) const
	{
		return x == other.x && y == other.y;
	}

	// In tiles!
	int getDistance(const Vec2Tile & other) const
	{
		return (int)sqrtf((float)(x - other.x) * (x - other.x) + (float)(y - other.y) * (y - other.y));
	}
};

/*
	enum of available tile resources
*/
enum class TileResource
{
	TR_GROUND,
	TR_ROCK,

	TR_BUSH1,
	TR_BUSH2,
	TR_BUSH3,
	TR_BUSH4,
	TR_BUSH5,
	TR_BUSH6
};

class Field
{
public:
	static const int FIELD_HEIGHT = 25;
	static const int FIELD_WIDTH = 25;

	virtual TileResource getLayer1TileResource(const Vec2Tile & tile) const = 0;
	virtual TileResource getLayer2TileResource(const Vec2Tile & tile) const = 0;

	virtual ~Field() {}
};

#endif // !FIELD
