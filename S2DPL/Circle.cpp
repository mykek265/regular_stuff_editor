#include "Circle.h"

void init0(int& type, b2BodyDef& bdef, sf::CircleShape* circ)
{
	if (type == 0){
		bdef.type = b2_staticBody;
		circ->setFillColor(s2dpl::stat);
	}
	else if (type == 1){
		bdef.type = b2_dynamicBody;
		circ->setFillColor(s2dpl::dynam);
	}
	else if (type == 2){
		bdef.type = b2_kinematicBody;
		circ->setFillColor(s2dpl::kinem);
	}
}
//инициализация
s2dpl::Circle::Circle(b2World& sworld, sf::RenderWindow& swindow, float x, float y, float r, int type)
{
	world = &sworld;
	window = &swindow;
	pos.x = x;
	pos.y = y;
	angle = 0.f;
	sf::CircleShape* circ = new sf::CircleShape();
	circ->setPosition(pos);
	circ->setRadius(r);
	circ->setOrigin(r, r);
	b2BodyDef bdef;
	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
	b2CircleShape shape;
	shape.m_radius = r / s2dpl::SCALE;
	init0(type, bdef, circ);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&shape, 1.f);
	circle.push_back(*circ);
	delete circ;
}
s2dpl::Circle::Circle(b2World& sworld, sf::RenderWindow& swindow, float x, float y, float r, float density, int type)
{
	world = &sworld;
	window = &swindow;
	pos.x = x;
	pos.y = y;
	angle = 0.f;
	sf::CircleShape* circ = new sf::CircleShape();
	circ->setPosition(pos);
	circ->setRadius(r);
	circ->setOrigin(r, r);
	b2BodyDef bdef;
	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
	b2CircleShape shape;
	shape.m_radius = r / s2dpl::SCALE;
	init0(type, bdef, circ);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&shape, density);
	circle.push_back(*circ);
	delete circ;
}
s2dpl::Circle::Circle(b2World& sworld, sf::RenderWindow& swindow, float x, float y, float r, float density, float elasticity, float friction, int type)
{
	world = &sworld;
	window = &swindow;
	pos.x = x;
	pos.y = y;
	angle = 0.f;
	sf::CircleShape* circ = new sf::CircleShape();
	circ->setPosition(pos);
	circ->setRadius(r);
	circ->setOrigin(r, r);
	b2BodyDef bdef;
	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
	b2CircleShape shape;
	shape.m_radius = r / s2dpl::SCALE;
	init0(type, bdef, circ);
	physics = world->CreateBody(&bdef);
	b2FixtureDef fdef;
	fdef.density = density;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	fdef.shape = &shape;
	physics->CreateFixture(&fdef);
	circle.push_back(*circ);
	delete circ;
}
s2dpl::Circle::Circle(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, float r, int type)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = 0.f;
	sf::CircleShape* circ = new sf::CircleShape();
	circ->setPosition(pos);
	circ->setRadius(r);
	circ->setOrigin(r, r);
	b2BodyDef bdef;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	b2CircleShape shape;
	shape.m_radius = r / s2dpl::SCALE;
	init0(type, bdef, circ);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&shape, 1.f);
	circle.push_back(*circ);
	delete circ;
}
s2dpl::Circle::Circle(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, float r, float density, int type)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = 0.f;
	sf::CircleShape* circ = new sf::CircleShape();
	circ->setPosition(pos);
	circ->setRadius(r);
	circ->setOrigin(r, r);
	b2BodyDef bdef;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	b2CircleShape shape;
	shape.m_radius = r / s2dpl::SCALE;
	init0(type, bdef, circ);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&shape, density);
	circle.push_back(*circ);
	delete circ;
}
s2dpl::Circle::Circle(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, float r, float density, float elasticity, float friction, int type)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = 0.f;
	sf::CircleShape* circ = new sf::CircleShape();
	circ->setPosition(pos);
	circ->setRadius(r);
	circ->setOrigin(r, r);
	b2BodyDef bdef;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	b2CircleShape shape;
	shape.m_radius = r / s2dpl::SCALE;
	init0(type, bdef, circ);
	physics = world->CreateBody(&bdef);
	b2FixtureDef fdef;
	fdef.density = density;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	fdef.shape = &shape;
	physics->CreateFixture(&fdef);
	circle.push_back(*circ);
	delete circ;
}


s2dpl::Circle::~Circle()
{
}
