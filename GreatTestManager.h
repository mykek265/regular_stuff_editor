#ifndef GREATTESTMANAGER_H
#define GREATTESTMANAGER_H
#include "s2dpl.h"
#include "CoolMenu.h"
#include "CoolJointManager.h"
#include "CoolFigureEditor.h"

//the
class GreatTestManager
{
	static std::vector<s2dpl::Primitiv*>	primitiv;
	static std::vector<s2dpl::RevJoint*>	revjoint;
	static std::vector<s2dpl::PrismJoint*>	prismjoint;
	static sf::RenderWindow*				window;
	static b2World*							world;
	static std::vector<PrimitivBluePr>*		blpr;
	void loadJ(JointBluePr& blueprint);
	static void loadSpr(std::vector<sf::Sprite>::iterator& begin, int size);
private:
	s2dpl::Primitiv* lload(PrimitivBluePr& blueprint);
public:
	bool work;
	GreatTestManager();
	GreatTestManager(sf::RenderWindow& window, b2World& world);
	void load(std::vector<PrimitivBluePr>& blueprint, CoolJointManager& manager);
	void draw();
	void stop();
	~GreatTestManager();
};
#endif
