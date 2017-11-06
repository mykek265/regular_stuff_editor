#include "ServoPrismJoint.h"





s2dpl::ServoPrismJoint::ServoPrismJoint()
{
}

s2dpl::ServoPrismJoint::ServoPrismJoint(b2World* w, const Primitiv& A, const Primitiv& B, const sf::Vector2f& Apos, const sf::Vector2f& Bpos, const sf::Vector2f& normal)//Free RevJoint
{
	world = w;
	achieved = false;
	speed = 0.f;
	force = 0.f;
	b2PrismaticJointDef jdef;
	jdef.bodyA = A.physics;
	jdef.bodyB = B.physics;
	jdef.localAnchorA = b2Vec2(Apos.x / s2dpl::SCALE, -Apos.y / s2dpl::SCALE);
	jdef.localAnchorB = b2Vec2(Bpos.x / s2dpl::SCALE, -Bpos.y / s2dpl::SCALE);
	jdef.localAxisA = b2Vec2(normal.x, -normal.y);
	j = (b2PrismaticJoint*)A.world->CreateJoint(&jdef);
}

void s2dpl::ServoPrismJoint::setDistance(const float& d)
{
	distance = d;
	//ќтрицательна€ дельта альфа если нужна отрицательна€ скорость, положительное если положительное
	float dd = distance*s2dpl::GtoR - j->GetJointTranslation();
	//ѕолучаем моментальную скорость
	float sp;
	j->EnableMotor(true);
	if (dd > 0.1 && dd < -0.1) achieved = true;
	else{
		sp = dd*speed;
		achieved = false;
	}
	if (!achieved){//если угол не достигнут, то крутить
		j->SetMotorSpeed(dd>0 ? sp*sp * 5 : -sp*sp * 5);
		j->SetMaxMotorForce(force);
	}
}

s2dpl::ServoPrismJoint::~ServoPrismJoint()//вызываетс€ перед ~RevJoint()
{
	world->DestroyJoint(j);
	j = NULL;
}
