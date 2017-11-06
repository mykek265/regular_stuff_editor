#ifndef PRIMITIV_H
#define PRIMITIV_H
#include "s2dplDefenitions.h"
#include "Sensor.h"
#include "RectSensor.h"

namespace s2dpl
{
	class Primitiv
	{
	protected:
		static sf::RenderWindow*			window;
		std::vector<sf::RectangleShape>		rectangle;
		std::vector<sf::CircleShape>		circle;
		std::vector<sf::ConvexShape>		triangle;
		std::vector<sf::Sprite>				sprite;
		std::vector<b2Joint*>				jj;
		std::vector<Sensor*>				ptrSensor;
		uint16								im;
		uint16								iColWth;
		void juggleV(sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3);
		template<typename T>
		void setColor(const b2BodyType& type, T* shape)
		{
			if (type == b2_staticBody)
				shape->setFillColor(stat);
			if (type == b2_kinematicBody)
				shape->setFillColor(kinem);
			if (type == b2_dynamicBody)
				shape->setFillColor(dynam);
		}
	public:
		static b2World*					world;
		b2Body*							physics;
		sf::Vector2f					pos;
		float							angle;

		Primitiv();
		Primitiv(b2World& sworld, sf::RenderWindow& swindow, const sf::Vector2f& pos, int type);
		Primitiv(b2World& sworld, sf::RenderWindow& swindow, const sf::Vector2f& pos, float density, float friction, float elasticity, int type, const uint16& im, const uint16& icol);

		void draw();
		//-----------------------------------------------------------//
		//--------------------Добавление форм------------------------//
		//-----------------------------------------------------------//

		//void addRect(float ox, float oy, float w, float h);
		//void addRect(float ox, float oy, float w, float h, float density);
		//void addRect(float ox, float oy, float w, float h, float density, float elasticity, float friction);
		//void addCirc(float ox, float oy, float r);
		//void addCirc(float ox, float oy, float r, float density);
		//void addCirc(float ox, float oy, float r, float density, float elasticity, float friction);
		//void addTriang(float ox, float oy, sf::Vector2f v3[]);
		//void addTriang(float ox, float oy, sf::Vector2f v3[], float density);
		//void addTriang(float ox, float oy, sf::Vector2f v3[], float density, float elasticity, float friction);
		void addRect(sf::Vector2f pos, sf::Vector2f size);
		void addRect(sf::Vector2f pos, sf::Vector2f size, float density);
		void addRect(sf::Vector2f pos, sf::Vector2f size, float density, float friction, float elasticity);
		//----------------------------------------------
		void addCirc(sf::Vector2f pos, float r);
		void addCirc(sf::Vector2f pos, float r, float density);
		void addCirc(sf::Vector2f pos, float r, float density, float friction, float elasticity);
		//----------------------------------------------
		void addTriang(sf::Vector2f& pos, sf::Vector2f v3[]);
		void addTriang(sf::Vector2f pos, sf::Vector2f v3[], float density);
		void addTriang(sf::Vector2f pos, sf::Vector2f v3[], float density, float friction, float elasticity);
		//----------------------------------------------
		void addImg(sf::Sprite sprite);
		//----------------------------------------------
		s2dpl::Sensor* addSensor(sf::Vector2f pos, sf::Vector2f size);
		//----------------------------------------------
		~Primitiv();
	};
}



#endif