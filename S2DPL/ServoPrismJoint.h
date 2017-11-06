#ifndef SERVOPRISMJOINT_H
#define SERVOPRISMJOINT_H
#include "../s2dpl.h"
#include "PrismJoint.h"
namespace s2dpl
{
	class ServoPrismJoint :
		public s2dpl::PrismJoint
	{
	public:
		ServoPrismJoint();
		ServoPrismJoint(b2World* world, const Primitiv& A, const Primitiv& B, const sf::Vector2f& Apos, const sf::Vector2f& Bpos, const sf::Vector2f& normal);
		void setDistance(const float& distance);
		~ServoPrismJoint();
	};

}

#endif