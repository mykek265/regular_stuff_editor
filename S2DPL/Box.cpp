#include "Box.h"

inline void init0(int& type, b2BodyDef& bdef, sf::RectangleShape* rect)
{
	if (type == 0){
		bdef.type = b2_staticBody;
		rect->setFillColor(s2dpl::stat);
	}
	else if (type == 1){
		bdef.type = b2_dynamicBody;
		rect->setFillColor(s2dpl::dynam);
	}
	else if (type == 2){
		bdef.type = b2_kinematicBody;
		rect->setFillColor(s2dpl::kinem);
	}
}
//инициализация
s2dpl::Box::Box(b2World& sworld, sf::RenderWindow& swindow, float x, float y, float w, float h, int type)
{
	world = &sworld;
	window = &swindow;
	pos.x = x;
	pos.y = y;
	angle = 0.f;
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setPosition(pos);
	rect->setSize(sf::Vector2f(w * 2, h * 2));
	rect->setOrigin(w, h);
	b2BodyDef bdef;
	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(std::abs(w) / s2dpl::SCALE, std::abs(h) / s2dpl::SCALE);
	init0(type, bdef, rect);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&shape, 1.f);
	rectangle.push_back(*rect);
	delete rect;
}
s2dpl::Box::Box(b2World& sworld, sf::RenderWindow& swindow, float x, float y, float w, float h, float density, int type)
{
	world = &sworld;
	window = &swindow;
	pos.x = x;
	pos.y = y;
	angle = 0.f;
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setPosition(pos);
	rect->setSize(sf::Vector2f(w * 2, h * 2));
	rect->setOrigin(w, h);
	b2BodyDef bdef;
	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(std::abs(w) / s2dpl::SCALE, std::abs(h) / s2dpl::SCALE);
	init0(type, bdef, rect);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&shape, density);
	rectangle.push_back(*rect);
	delete rect;
}
s2dpl::Box::Box(b2World& sworld, sf::RenderWindow& swindow, float x, float y, float w, float h, float sangle, float density, int type)
{
	world = &sworld;
	window = &swindow;
	pos.x = x;
	pos.y = y;
	angle = sangle;
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setPosition(pos);
	rect->setSize(sf::Vector2f(w * 2, h * 2));
	rect->setOrigin(w, h);
	b2BodyDef bdef;
	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
	bdef.angle = angle;
	b2PolygonShape shape;
	shape.SetAsBox(std::abs(w) / s2dpl::SCALE, std::abs(h) / s2dpl::SCALE);
	init0(type, bdef, rect);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&shape, density);
	rectangle.push_back(*rect);
	delete rect;
}
s2dpl::Box::Box(b2World& sworld, sf::RenderWindow& swindow, float x, float y, float w, float h, float density, float elasticity, float friction, int type)
{
	world = &sworld;
	window = &swindow;
	pos.x = x;
	pos.y = y;
	angle = 0.f;
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setPosition(pos);
	rect->setSize(sf::Vector2f(w * 2, h * 2));
	rect->setOrigin(w, h);
	b2BodyDef bdef;
	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(std::abs(w) / s2dpl::SCALE, std::abs(h) / s2dpl::SCALE);
	b2FixtureDef fdef;
	fdef.shape=&shape;
	fdef.density = density;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	init0(type, bdef, rect);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&fdef);
	rectangle.push_back(*rect);
	delete rect;
}
s2dpl::Box::Box(b2World& sworld, sf::RenderWindow& swindow, float x, float y, float w, float h, float sangle, float density, float elasticity, float friction, int type)
{
	world = &sworld;
	window = &swindow;
	pos.x = x;
	pos.y = y;
	angle = sangle;
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setPosition(pos);
	rect->setSize(sf::Vector2f(w * 2, h * 2));
	rect->setOrigin(w, h);
	b2BodyDef bdef;
	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
	bdef.angle = angle;
	b2PolygonShape shape;
	shape.SetAsBox(std::abs(w) / s2dpl::SCALE, std::abs(h) / s2dpl::SCALE);
	b2FixtureDef fdef;
	fdef.shape = &shape;
	fdef.density = density;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	init0(type, bdef, rect);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&fdef);
	rectangle.push_back(*rect);
	delete rect;
}
s2dpl::Box::Box(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, sf::Vector2f size, int type)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = 0.f;
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setPosition(pos);
	rect->setSize(sf::Vector2f(size.x * 2, size.y * 2));
	rect->setOrigin(size);
	b2BodyDef bdef;
	bdef.position.Set(spos.x / s2dpl::SCALE, -spos.y / s2dpl::SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(std::abs(size.x) / s2dpl::SCALE, std::abs(size.y) / s2dpl::SCALE);
	init0(type, bdef, rect);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&shape, 1.f);
	rectangle.push_back(*rect);
	delete rect;
}
s2dpl::Box::Box(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, sf::Vector2f size, float density, int type)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = 0.f;
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setPosition(pos);
	rect->setSize(sf::Vector2f(size.x * 2, size.y * 2));
	rect->setOrigin(size);
	b2BodyDef bdef;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(std::abs(size.x) / s2dpl::SCALE, std::abs(size.y) / s2dpl::SCALE);
	init0(type, bdef, rect);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&shape, density);
	rectangle.push_back(*rect);
	delete rect;
}
s2dpl::Box::Box(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, sf::Vector2f size, float density, float sangle, int type)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = sangle;
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setPosition(pos);
	rect->setSize(sf::Vector2f(size.x * 2, size.y * 2));
	rect->setOrigin(size);
	b2BodyDef bdef;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	bdef.angle = angle;
	b2PolygonShape shape;
	shape.SetAsBox(std::abs(size.x) / s2dpl::SCALE, std::abs(size.y) / s2dpl::SCALE);
	init0(type, bdef, rect);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&shape, density);
	rectangle.push_back(*rect);
	delete rect;
}
s2dpl::Box::Box(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, sf::Vector2f size, float density, float friction, float elasticity, int type, uint16 im, uint16 icol)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = 0.f;
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setPosition(pos);
	rect->setSize(sf::Vector2f(size.x * 2, size.y * 2));
	rect->setOrigin(size);
	b2BodyDef bdef;
	bdef.position.Set(spos.x / s2dpl::SCALE, -spos.y / s2dpl::SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(std::abs(size.x) / s2dpl::SCALE, std::abs(size.y) / s2dpl::SCALE);
	b2FixtureDef fdef;
	fdef.shape = &shape;
	fdef.density = density;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	fdef.filter.categoryBits = im;
	fdef.filter.maskBits = icol;
	init0(type, bdef, rect);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&fdef);
	rectangle.push_back(*rect);
	delete rect;
}
s2dpl::Box::Box(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, sf::Vector2f size, float density, float sangle, float elasticity, float friction, int type)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = sangle;
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setPosition(pos);
	rect->setSize(sf::Vector2f(size.x * 2, size.y * 2));
	rect->setOrigin(size);
	b2BodyDef bdef;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(size.x / s2dpl::SCALE, size.y / s2dpl::SCALE);
	b2FixtureDef fdef;
	fdef.shape = &shape;
	fdef.density = density;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	init0(type, bdef, rect);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&fdef);
	rectangle.push_back(*rect);
	delete rect;
}



s2dpl::Box::~Box()
{
}
