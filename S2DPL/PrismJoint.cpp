#include "PrismJoint.h"
b2World* s2dpl::PrismJoint::world(NULL);


s2dpl::PrismJoint::PrismJoint()
{}

s2dpl::PrismJoint::PrismJoint(b2World* w, const Primitiv& A, const Primitiv& B, const sf::Vector2f& normal)
	:speed(0.f),
	force(0.f),
	achieved(false),
	servo(false)
{
	world = w;
	b2PrismaticJointDef jdef;
	jdef.bodyA = A.physics;
	jdef.bodyB = B.physics;
	jdef.localAxisA = b2Vec2(normal.x, -normal.y);
	j = (b2PrismaticJoint*)A.world->CreateJoint(&jdef);
}
s2dpl::PrismJoint::PrismJoint(b2World* w, const Primitiv& A, const Primitiv& B, const sf::Vector2f& Apos, const sf::Vector2f& Bpos, sf::Vector2f& normal)//Free RevJoint
	:speed(0.f),
	force(0.f),
	achieved(false),
	servo(false)
{
	world = w;
	b2PrismaticJointDef jdef;
	jdef.bodyA = A.physics;
	jdef.bodyB = B.physics;
	jdef.localAnchorA = b2Vec2(Apos.x / s2dpl::SCALE, -Apos.y / s2dpl::SCALE);
	jdef.localAnchorB = b2Vec2(Bpos.x / s2dpl::SCALE, -Bpos.y / s2dpl::SCALE);
	jdef.localAxisA = b2Vec2(normal.x, -normal.y);
	j = (b2PrismaticJoint*)A.world->CreateJoint(&jdef);
}
//мотор
void s2dpl::PrismJoint::onMotor(const float& lspeed, const float& lforce)
{
	speed = lspeed;
	force = lforce;
	j->EnableMotor(true);
	j->SetMotorSpeed(speed);
	j->SetMaxMotorForce(force);
}
void s2dpl::PrismJoint::setSpeedForce(const float& lspeed, const float& lforce)
{
	speed = lspeed;
	force = lforce;
}
void s2dpl::PrismJoint::offMotor()
{
	j->EnableMotor(false);
	achieved = false;
	speed = 0.f;
	force = 0.f;
}
//лимит
void s2dpl::PrismJoint::onLimit(const float& min, const float& max)
{
	j->EnableLimit(true);
	j->SetLimits(min / s2dpl::SCALE, max / s2dpl::SCALE);
}
void s2dpl::PrismJoint::offLimit()
{
	j->EnableLimit(false);
}

//интерфейс сервопривода
void s2dpl::PrismJoint::setDistance(const float& distance)
{}


s2dpl::PrismJoint::~PrismJoint()
{
	world->DestroyJoint(j);
	j = NULL;
}
