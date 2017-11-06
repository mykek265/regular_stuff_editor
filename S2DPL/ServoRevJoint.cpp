#include "ServoRevJoint.h"


float angle;
float speed;
float force;
bool achieved;


s2dpl::ServoRevJoint::ServoRevJoint()
{
}

s2dpl::ServoRevJoint::ServoRevJoint(b2World* w, Primitiv& A, Primitiv& B, sf::Vector2f Apos, sf::Vector2f Bpos)//Free RevJoint
{
	world = w;
	achieved = false;
	speed = 0.f;
	force = 0.f;
	b2RevoluteJointDef jdef;
	jdef.bodyA = A.physics;
	jdef.bodyB = B.physics;
	jdef.localAnchorA = b2Vec2(Apos.x / s2dpl::SCALE, -Apos.y / s2dpl::SCALE);
	jdef.localAnchorB = b2Vec2(Bpos.x / s2dpl::SCALE, -Bpos.y / s2dpl::SCALE);
	j = (b2RevoluteJoint*)A.world->CreateJoint(&jdef);
	angle = j->GetJointAngle()*RtoG;
}

void s2dpl::ServoRevJoint::setAngle(float a)
{
	angle = a;
	//ќтрицательна€ дельта альфа если нужна отрицательна€ скорость, положительное если положительное
	float da = angle*s2dpl::GtoR - j->GetJointAngle();
	//ѕолучаем моментальную скорость
	float sp;
	j->EnableMotor(true);
	if (da > 0.1 && da < -0.1) achieved = true;
	else{
		sp = da*speed;
		achieved = false;
	}
	if (!achieved){//если угол не достигнут, то крутить
		j->SetMotorSpeed(da>0 ? sp*sp * 5 : -sp*sp * 5);
		j->SetMaxMotorTorque(force);
	}
}

s2dpl::ServoRevJoint::~ServoRevJoint()//вызываетс€ перед ~RevJoint()
{
	world->DestroyJoint(j);
	j = NULL;
}
