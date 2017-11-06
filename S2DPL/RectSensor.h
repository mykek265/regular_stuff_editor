#ifndef RECSENSOR_H
#define RECSENSOR_H
#include "Sensor.h"
#include "../toString.h"
namespace s2dpl
{
	class RectSensor:
		public Sensor
	{
	public:
		RectSensor(b2World* world, sf::RenderWindow* window, float x, float y, float w, float h);
		RectSensor(bool soed, float x, float y, float w, float h);
		RectSensor(b2World* world, sf::RenderWindow* window, float x, float y, float w, float h, float density);
		RectSensor(b2World* world, sf::RenderWindow* window, float x, float y, float w, float h, float angle, float density);
		//Вот что буду использовать в StaffEditor!!!
		RectSensor(bool soed, sf::Vector2f pos, sf::Vector2f size, uint16 dontCountThis);
		RectSensor(sf::Vector2f pos, sf::Vector2f size, float density);
		RectSensor(sf::Vector2f pos, sf::Vector2f size, float density, float angle);
		~RectSensor();
	};
}
#endif

