#ifndef CURRENT_STATS

#include <unordered_map>
#include "Objects/Node.h"
#include "Objects/TextLabel.h"
#include "Entities/Warrior.h"

#define FONT_PATH "../Resources/Fonts/Kurale.ttf"
#define FONT_SIZE 24

class CurrentStats : public Node
{
private:
	std::shared_ptr<Warrior> warrior;

/*	std::shared_ptr<TextLabel> levelLabel;
	std::shared_ptr<TextLabel> expirienceLabel;
	std::shared_ptr<TextLabel> hitsLabel;
	std::shared_ptr<TextLabel> attackLabel;
	std::shared_ptr<TextLabel> defenseLabel;
	*/
	std::unordered_map<std::string, std::shared_ptr<TextLabel>> labels;

public:
	CurrentStats(std::shared_ptr<Warrior> _warrior);
	virtual ~CurrentStats() {}

private:
	virtual void updateLabelsPosition(Vec2 thisPos);
	virtual Vec2 getLabelPosition(int labelIdx);
private:
	virtual void _setParent(NodePtr _parent) override;

public:
	virtual void setPosition(float _x, float _y) override;
	virtual void update(float dt) override;
};

#endif // !CURRENT_STATS
