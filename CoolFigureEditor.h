#ifndef COOLFIGUREEDITOR_H
#define COOLFIGUREEDITOR_H
#include <SFML\Graphics.hpp>
#include <algorithm>
#include <vector>

class CoolFigureEditor
{
private:
	static sf::RenderWindow*	window;
	static sf::Clock			KWP;
	static sf::Time				KWPline;
	static bool					circleTrig, newConv;
	static sf::CircleShape*		circleBrush;
	static sf::RectangleShape*	rectBrush;
	static sf::ConvexShape*		convBrush;
	static int					lastPolNo, clkm2;
	static bool					rectTrig;
	static sf::Vector2f			pointForS[3];
	static int					state;
	static sf::Vector2f			sdvig;
	static sf::RectangleShape	rectM;
	static sf::CircleShape		circleM;
	static sf::ConvexShape		triangM;

	static void updateMenuColor();

public:
	static sf::CircleShape			center;
	std::vector<sf::RectangleShape>	rect;
	std::vector<sf::CircleShape>	circle;
	std::vector<sf::ConvexShape>	triangle;
	CoolFigureEditor();
	CoolFigureEditor(sf::RenderWindow& window);
	void swUp();
	void swDown();
	void Mod3();
	void draw();
	~CoolFigureEditor();
};

#endif