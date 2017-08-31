#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Objects/Node.h"
#include "GameMap/Field.h"

enum class SpriteResource
{
	SR_VAPIRE1,
	SR_SKELETON1,
	SR_VAPIRE2,
	SR_SKELETON2,

	SR_ITEM1,
	SR_ITEM2,
	SR_ITEM3,

	SR_WARRIOR
};

enum class SpriteAnimation
{
	SA_IDLE,
	SA_ATTACK,
	SA_HIT
};

class Entity
{
public:
	virtual const std::string & getName() const = 0;
	virtual SpriteResource getResource() const = 0;

	virtual const Vec2Tile & getTile() const = 0;
	virtual ~Entity() {}
};

#endif // !ENTITY_H
