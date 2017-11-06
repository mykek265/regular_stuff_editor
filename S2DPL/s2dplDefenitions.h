#ifndef S2DPlDEFENITIONS_H
#define S2DPlDEFENITIONS_H
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>
#include <vector>

namespace s2dpl
{ /*“ут объ€вл€ютс€ константы, которые подгружаютс€ до подключени€ классов S2DPL*/
	static const float RtoG = 57.2958f;
	static const float GtoR = 0.0174533f;
	static const float SCALE = 30.f;
	static const sf::Color stat(sf::Color(32, 139, 24, 200));
	static const sf::Color kinem(sf::Color(89, 24, 139, 200));
	static const sf::Color dynam(sf::Color(215, 143, 62, 200));
	static const sf::Color sensorOn(sf::Color(81, 205, 255, 200));
	static const sf::Color sensorOff(sf::Color(10, 71, 255, 200));
}

#endif