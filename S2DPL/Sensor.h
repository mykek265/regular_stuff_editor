#ifndef SENSOR_H
#define SENSOR_H
#include "s2dplDefenitions.h"
#include <vector>

namespace s2dpl
{
	class Sensor
	{
	public:
	//хранилище строк по которым можно сразу найти нужное тело
		std::string id;
		static std::map<std::string, Sensor*> sensor;//все сенсоры, которые когда-либо существовали 
		static std::vector<std::string> deleted;
		int No;//порядковый номер в этих списках
		b2Body* physics;
	protected:
		sf::Vector2f pos;
		float angle;
		sf::RectangleShape			rectangle;
		int							contact;
		static	b2World*			world;
		static	sf::RenderWindow*	window;
	public:
		Sensor();
		~Sensor();
		void startContact();
		void endContact();
		int speak();//слушать, что скажет
		void draw();//посмотреть, где находится
		//Можно настроить класс за один раз
		static void init(b2World& world, sf::RenderWindow& window);
	};
}

#endif