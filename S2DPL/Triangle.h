#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Primitiv.h"
namespace s2dpl
{
	class Triangle :
		public s2dpl::Primitiv
	{
	public:

		//инициализация
		Triangle(b2World& world, sf::RenderWindow& window, float x, float y, sf::Vector2f v3[], int type);
		Triangle(b2World& world, sf::RenderWindow& window, float x, float y, sf::Vector2f v3[], float dencity, int type);
		Triangle(b2World& world, sf::RenderWindow& window, float x, float y, sf::Vector2f v3[], float dencity, float elasticity, float friction, int type);
		Triangle(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f v3[], int type);
		Triangle(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f v3[], float dencity, int type);
		Triangle(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f v3[], float dencity, float elasticity, float friction, int type);
		
		~Triangle();
	};
}

#endif