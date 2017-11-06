#ifndef SERVOREVJOINT_H
#define SERVOREVJOINT_H
#include "../s2dpl.h"
#include "RevJoint.h"
namespace s2dpl
{
	class ServoRevJoint: 
		public s2dpl::RevJoint
	{
	public:
		ServoRevJoint();
		ServoRevJoint(b2World* world, Primitiv& A, Primitiv& B, sf::Vector2f Apos, sf::Vector2f Bpos);
		void setAngle(float a);
		~ServoRevJoint();
	};

}

#endif