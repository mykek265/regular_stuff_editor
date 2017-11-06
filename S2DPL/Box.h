#ifndef BOX_H
#define BOX_H
#include "Primitiv.h"

namespace s2dpl
{
	class Box :
		public s2dpl::Primitiv
	{
	public:

		//инициализация
		Box(b2World& world, sf::RenderWindow& window, float x, float y, float w, float h, int type);
		Box(b2World& world, sf::RenderWindow& window, float x, float y, float w, float h, float density, int type);
		Box(b2World& world, sf::RenderWindow& window, float x, float y, float w, float h, float angle, float density, int type);
		Box(b2World& world, sf::RenderWindow& window, float x, float y, float w, float h, float density, float elasticity, float friction, int type);
		Box(b2World& world, sf::RenderWindow& window, float x, float y, float w, float h, float angle, float density, float elasticity, float friction, int type);
		Box(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size, int type);
		Box(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size, float density, int type);
		Box(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size, float density, float angle, int type);
		Box(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size, float density, float friction, float elasticity, int type, uint16 im, uint16 icol);
		Box(b2World& world, sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size, float density, float angle, float elasticity, float friction, int type);



		~Box();
	};
}
#endif