#ifndef ITEM
#define ITEM

#include <assert.h>
#include "Objects/Sprite.h"
#include "Entities/Stats.h"
#include "GameMap/Field.h"

class Item : public Sprite
{
private:
	std::string name;
	Vec2Tile position;
	bool picked;

	int attack;
	int defense;
	
private:
	virtual const std::string & getName() const;

public:
	int getAttack() const;
	int getDefense() const;

	void pick();
	bool isPicked() const;
	virtual const Vec2Tile & getTile() const;

public:
	Item() {}

	Item(
		const std::string & imgPath,
		const Vec2Tile & _position,
		const std::string & _name,
		int _defense,
		int _attack)
		: Sprite(imgPath)
	{
		assert(_name.size() > 0);
		assert(_attack >= 0);
		assert(_defense >= 0);

		position = _position;
		name = _name;

		defense = _defense;
		attack = _attack;
		picked = false;
	}

	virtual ~Item() {}
};

#endif // !ITEM
