#ifndef COOLFEATUREWINDOW_H
#define COOLFEATUREWINDOW_H
#include <SFML\Graphics.hpp>
#include "toString.h"
#include "Box2D\Box2D.h"

class CoolFeatureWindow
{
private:
	static const int			Nstr = 46;
	static sf::RenderWindow*	window;
	static sf::RectangleShape	fon;
	static sf::Text				str[Nstr];
	static sf::Vector2f			sdvig, mouse;
	static std::string			strType[3];
	static bool					cwp;
	//static void setByDrag(float& value);
public:
	static int					type;
	static float				density, friction, elasticity;
	static bool					im[16];
	static bool					icolwith[16];
	static bool					active;
	CoolFeatureWindow();
	CoolFeatureWindow(sf::RenderWindow& window, sf::Font& font);

	short draw();

	~CoolFeatureWindow();
};
#endif
