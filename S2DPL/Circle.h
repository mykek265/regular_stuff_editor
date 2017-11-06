#ifndef CIRCLE_H
#define CIRCLE_H
#include "Primitiv.h"
namespace s2dpl
{
	class Circle :
		public s2dpl::Primitiv
	{
	public:

		//инициализация
		Circle(b2World& world, sf::RenderWindow& window, float x, float y, float r, int type);
		Circle(b2World& world, sf::RenderWindow& window, float x, float y, float r, float density, int type);
		Circle(b2World& world, sf::RenderWindow& window, float x, float y, float r, float density, float elasticity, float friction, int type);
		Circle(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, float r, int type);
		Circle(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, float r, float density, int type);
		Circle(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, float r, float density, float elasticity, float friction, int type);


		~Circle();
	};
}
#endif