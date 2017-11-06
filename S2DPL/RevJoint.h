#ifndef REVJOINT_H
#define REVJOINT_H
#include"Box.h"
#include"Circle.h"
#include"Triangle.h"
#include"Primitiv.h"

namespace s2dpl
{
	class RevJoint
	{
	protected:
		static b2World* world;
		float angle;
		float speed;
		float force;
		bool achieved;
		bool servo;
	public:
		b2RevoluteJoint* j;
		RevJoint();
		RevJoint(b2World* world, Primitiv& A, Primitiv& B);
		RevJoint(b2World* world, Primitiv& A, Primitiv& B, sf::Vector2f Apos, sf::Vector2f Bpos);
		//мотор
		void onMotor(const float& speed, const float& force);
		void setSpeedForce(const float& speed, const float& force);
		void offMotor();
		//лимит
		void onLimit(float min, float max);
		void offLimit();
		//интерфейс сервопривода
		virtual void setAngle(float angle);

		float getAngle();
		float getSpeed();
		float getForce();
		~RevJoint();
	};
}

#endif