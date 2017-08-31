#ifndef ITEM
#define ITEM

#include <assert.h>
#include "Entities/Entity.h"
#include "Entities/Stats.h"

class Item : public Entity
{
private:
	std::string name;
	Vec2Tile position;
	SpriteResource spriteResource;
	bool picked;

	int attack;
	int defense;
	
private:
	virtual const std::string & getName() const override;
	virtual SpriteResource getResource() const override;
	virtual const Vec2Tile & getTile() const override;

public:
	int getAttack() const;
	int getDefense() const;

	void pick();
	bool isPicked() const;
	const Vec2Tile & getPosition() const;

public:
	Item() {}

	Item(
		const SpriteResource & _spriteResource,
		const Vec2Tile & _position,
		const std::string & _name,
		int _defense,
		int _attack)
	{
		assert(_name.size() > 0);
		assert(_attack >= 0);
		assert(_defense >= 0);

		spriteResource = _spriteResource;
		position = _position;
		name = _name;

		defense = _defense;
		attack = _attack;
		picked = false;
	}

	virtual ~Item() {}
};

#endif // !ITEM
