#include "RevJoint.h"
b2World* s2dpl::RevJoint::world(NULL);


s2dpl::RevJoint::RevJoint()
{}

s2dpl::RevJoint::RevJoint(b2World* w,Primitiv& A, Primitiv& B)
	:angle(0.f),
	speed(0.f),
	force(0.f),
	achieved(false),
	servo(false)
{
	world = w;
	b2RevoluteJointDef jdef;
	jdef.bodyA = A.physics;
	jdef.bodyB = B.physics;
	j = (b2RevoluteJoint*)A.world->CreateJoint(&jdef);
}
s2dpl::RevJoint::RevJoint(b2World* w, Primitiv& A, Primitiv& B, sf::Vector2f Apos, sf::Vector2f Bpos)//Free RevJoint
	:angle(0.f),
	speed(0.f),
	force(0.f),
	achieved(false),
	servo(false)
{
	world = w;
	b2RevoluteJointDef jdef;
	jdef.bodyA = A.physics;
	jdef.bodyB = B.physics;
	jdef.localAnchorA = b2Vec2(Apos.x / s2dpl::SCALE, -Apos.y / s2dpl::SCALE);
	jdef.localAnchorB = b2Vec2(Bpos.x / s2dpl::SCALE, -Bpos.y / s2dpl::SCALE);
	j = (b2RevoluteJoint*)A.world->CreateJoint(&jdef);
}
//мотор
void s2dpl::RevJoint::onMotor(const float& lspeed, const float& lforce)
{
	speed = lspeed;
	force = lforce;
	j->EnableMotor(true);
	j->SetMotorSpeed(speed);
	j->SetMaxMotorTorque(force);
}
void s2dpl::RevJoint::setSpeedForce(const float& lspeed, const float& lforce)
{
	speed = lspeed;
	force = lforce;
}
void s2dpl::RevJoint::offMotor()
{
	j->EnableMotor(false);
	achieved = false;
	speed = 0.f;
	force = 0.f;
}
//лимит
void s2dpl::RevJoint::onLimit(float min, float max)
{
	j->EnableLimit(true);
	j->SetLimits(min * s2dpl::GtoR, max * s2dpl::GtoR);
}
void s2dpl::RevJoint::offLimit()
{
	j->EnableLimit(false);
}

//интерфейс сервопривода
void s2dpl::RevJoint::setAngle(float angle)
{}


s2dpl::RevJoint::~RevJoint()
{
	world->DestroyJoint(j);
	j = NULL;
}
