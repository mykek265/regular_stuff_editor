#ifndef COOLJOINTMANAGER_H
#define COOLJOINTMANAGER_H
#include <algorithm>
#include "s2dpl.h"
#include "JointBluePr.h"
#include "PrimitivBluePr.h"
#include "CoolMenu.h"
#include "windowSize.h"

class CoolJointManager
{
private:
	static int							click;	//цикл кликов
	static bool							kwp;	//key was pressed
	static PrimitivBluePr				*pA;
	static PrimitivBluePr				*pB;
	static sf::RectangleShape			line[2];
	static float						zoom;
	static unsigned int					mustDie;//какое из соединений должно быть уничтожено
	static CoolMenu*					menu;
	void coolSettingsWindow();
	void newJointCreation(sf::Vector2f& mouse);
	template <typename T>
	void setLiteButton(const std::string& str0, const sf::Vector2f& center, const sf::Vector2f& fonOrg, const float& x, const float& y, const sf::Vector2f& mouse, int& question, const int& q, T& some, const T& type)
	{
		str.setPosition(sf::Vector2f(x*fonOrg.x, y*fonOrg.y) + center);
		str.setString(str0);
		str.setStyle(0);
		if (isButtonChoosen(str.getPosition(), mouse))
		{
			str.setStyle(1);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				some = type;
				question = q;
			}
		}
	}
public:
	static sf::RenderWindow*			window;
	static std::vector<JointBluePr>		joint;
	static sf::Text						str;
	CoolJointManager();
	CoolJointManager(sf::RenderWindow& w,	CoolMenu* menu);
	void draw();
	~CoolJointManager();
};

#endif