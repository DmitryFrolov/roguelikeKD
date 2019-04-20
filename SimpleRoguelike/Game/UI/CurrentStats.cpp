#include "CurrentStats.h"

CurrentStats::CurrentStats(std::shared_ptr<Warrior> _warrior)
{
	this->warrior = _warrior;

	labels.insert(std::make_pair("levelLabel", TextLabel::create(FONT_PATH, FONT_SIZE, "0")));
	labels.insert(std::make_pair("expirienceLabel", TextLabel::create(FONT_PATH, FONT_SIZE, "0")));
	labels.insert(std::make_pair("hitsLabel", TextLabel::create(FONT_PATH, FONT_SIZE, "0")));
	labels.insert(std::make_pair("attackLabel", TextLabel::create(FONT_PATH, FONT_SIZE, "0")));
	labels.insert(std::make_pair("defenseLabel", TextLabel::create(FONT_PATH, FONT_SIZE, "0")));

	for(auto label : labels)
		label.second->setAnchorPoint(0, 0.5);
}

void CurrentStats::updateLabelsPosition(Vec2 thisPos)
{
	int idx = 0;
	for (auto pair : labels)
	{
		pair.second->setPosition(getLabelPosition(idx));
		idx++;
	}
}

Vec2 CurrentStats::getLabelPosition(int labelIdx)
{
	float resY, indent = FONT_SIZE;
	int center = labels.size() / 2;
	resY = this->getPositionY() - indent * ((float)center - labelIdx);

	if (labels.size() % 2 != 0)
		return Vec2(this->getPositionX(), resY);
	else
		return Vec2(this->getPositionX(), resY + indent * 0.5);
}

void CurrentStats::setPosition(float _x, float _y)
{
	Node::setPosition(Vec2(_x, _y));
	updateLabelsPosition(Vec2(_x, _y));
}

void CurrentStats::update(float dt)
{
	labels["levelLabel"]->setString("lvl: " + std::to_string(warrior->getCurrentLevel()));
	labels["expirienceLabel"]->setString("exp: " + std::to_string(warrior->getExperience()));
	labels["hitsLabel"]->setString("Hits: " + std::to_string(warrior->getCurrentHits()) + "/" + std::to_string(warrior->getMaxHits()));
	labels["attackLabel"]->setString("Attack: " + std::to_string(warrior->getAttack()));
	labels["defenseLabel"]->setString("Defense: " + std::to_string(warrior->getDefense()));
}

void CurrentStats::_setParent(NodePtr _parent)
{
	this->addChild(labels["levelLabel"]);
	this->addChild(labels["expirienceLabel"]);
	this->addChild(labels["hitsLabel"]);
	this->addChild(labels["attackLabel"]);
	this->addChild(labels["defenseLabel"]);
	Node::_setParent(_parent);
}
