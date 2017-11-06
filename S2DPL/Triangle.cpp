#include "Triangle.h"

void init0(sf::Vector2f& pos, b2BodyDef& bdef, b2Vec2* vertices, sf::Vector2f* v3, int& type)
{
	if (type == 1) bdef.type = b2_dynamicBody;
	if (type == 2) bdef.type = b2_kinematicBody;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	vertices	  ->Set( v3		->x / s2dpl::SCALE, -( v3	  ->y / s2dpl::SCALE));
	(vertices + 1)->Set((v3 + 1)->x / s2dpl::SCALE, -((v3 + 1)->y / s2dpl::SCALE));
	(vertices + 2)->Set((v3 + 2)->x / s2dpl::SCALE, -((v3 + 2)->y / s2dpl::SCALE));
}

//инициализация
s2dpl::Triangle::Triangle(b2World& sworld, sf::RenderWindow& swindow, float x, float y, sf::Vector2f v3[], int type)
{
	world = &sworld;
	window = &swindow;
	pos = sf::Vector2f(x, y);
	angle = 0.f;
	sf::ConvexShape* conv = new sf::ConvexShape();
	s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
	conv->setPointCount(3);
	for (int i = 0; i < 3; i++)
		conv->setPoint(i, *(v3 + i));

	b2BodyDef bdef;

	b2Vec2 vertices[3];

	init0(pos, bdef, vertices, v3, type);

	b2PolygonShape convsh;
	convsh.Set(vertices, 3);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&convsh, 1.f);

	conv->setFillColor(stat);
	if (physics->GetType() == b2_kinematicBody)
		conv->setFillColor(kinem);
	if (physics->GetType() == b2_dynamicBody)
		conv->setFillColor(dynam);
	triangle.push_back(*conv);
	delete conv;
}
s2dpl::Triangle::Triangle(b2World& sworld, sf::RenderWindow& swindow, float x, float y, sf::Vector2f v3[], float dencity, int type)
{
	world = &sworld;
	window = &swindow;
	pos = sf::Vector2f(x, y);
	angle = 0.f;
	sf::ConvexShape* conv = new sf::ConvexShape();
	s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
	conv->setPointCount(3);
	for (int i = 0; i < 3; i++)
		conv->setPoint(i, *(v3 + i));

	b2BodyDef bdef;

	b2Vec2 vertices[3];

	init0(pos, bdef, vertices, v3, type);

	b2PolygonShape convsh;
	convsh.Set(vertices, 3);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&convsh, dencity);

	conv->setFillColor(stat);
	if (physics->GetType() == b2_kinematicBody)
		conv->setFillColor(kinem);
	if (physics->GetType() == b2_dynamicBody)
		conv->setFillColor(dynam);
	triangle.push_back(*conv);
	delete conv;
}
s2dpl::Triangle::Triangle(b2World& sworld, sf::RenderWindow& swindow, float x, float y, sf::Vector2f v3[], float dencity, float elasticity, float friction, int type)
{
	world = &sworld;
	window = &swindow;
	pos = sf::Vector2f(x, y);
	angle = 0.f;
	sf::ConvexShape* conv = new sf::ConvexShape();
	s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
	conv->setPointCount(3);
	for (int i = 0; i < 3; i++)
		conv->setPoint(i, *(v3 + i));

	b2BodyDef bdef;
	b2Vec2 vertices[3];

	init0(pos, bdef, vertices, v3, type);

	b2PolygonShape convsh;
	convsh.Set(vertices, 3);
	physics = world->CreateBody(&bdef);
	b2FixtureDef fdef;
	fdef.density = dencity;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	fdef.shape = &convsh;
	physics->CreateFixture(&fdef);

	conv->setFillColor(stat);
	if (physics->GetType() == b2_kinematicBody)
		conv->setFillColor(kinem);
	if (physics->GetType() == b2_dynamicBody)
		conv->setFillColor(dynam);
	triangle.push_back(*conv);
	delete conv;
}
s2dpl::Triangle::Triangle(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, sf::Vector2f v3[], int type)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = 0.f;
	sf::ConvexShape* conv = new sf::ConvexShape();
	s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
	conv->setPointCount(3);
	for (int i = 0; i < 3; i++)
		conv->setPoint(i, *(v3 + i));

	b2BodyDef bdef;
	b2PolygonShape convsh;
	b2Vec2 vertices[3];

	init0(pos, bdef, vertices, v3, type);

	convsh.Set(vertices, 3);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&convsh, 1.f);

	conv->setFillColor(stat);
	if (physics->GetType() == b2_kinematicBody)
		conv->setFillColor(kinem);
	if (physics->GetType() == b2_dynamicBody)
		conv->setFillColor(dynam);
	triangle.push_back(*conv);
	delete conv;
}
s2dpl::Triangle::Triangle(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, sf::Vector2f v3[], float dencity, int type)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = 0.f;
	sf::ConvexShape* conv = new sf::ConvexShape();
	s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
	conv->setPointCount(3);
	for (int i = 0; i < 3; i++)
		conv->setPoint(i, *(v3 + i));

	b2BodyDef bdef;
	b2PolygonShape convsh;
	b2Vec2 vertices[3];

	init0(pos, bdef, vertices, v3, type);

	convsh.Set(vertices, 3);
	physics = world->CreateBody(&bdef);
	physics->CreateFixture(&convsh, dencity);

	conv->setFillColor(stat);
	if (physics->GetType() == b2_kinematicBody)
		conv->setFillColor(kinem);
	if (physics->GetType() == b2_dynamicBody)
		conv->setFillColor(dynam);
	triangle.push_back(*conv);
	delete conv;
}
s2dpl::Triangle::Triangle(b2World& sworld, sf::RenderWindow& swindow, sf::Vector2f spos, sf::Vector2f v3[], float dencity, float elasticity, float friction, int type)
{
	world = &sworld;
	window = &swindow;
	pos = spos;
	angle = 0.f;
	sf::ConvexShape* conv = new sf::ConvexShape();
	s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
	conv->setPointCount(3);
	for (int i = 0; i < 3; i++)
		conv->setPoint(i, *(v3 + i));

	b2BodyDef bdef;
	b2PolygonShape convsh;
	b2Vec2 vertices[3];

	init0(pos, bdef, vertices, v3, type);

	convsh.Set(vertices, 3);
	physics = world->CreateBody(&bdef);
	b2FixtureDef fdef;
	fdef.density = dencity;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	fdef.shape = &convsh;
	physics->CreateFixture(&fdef);

	conv->setFillColor(stat);
	if (physics->GetType() == b2_kinematicBody)
		conv->setFillColor(kinem);
	if (physics->GetType() == b2_dynamicBody)
		conv->setFillColor(dynam);
	triangle.push_back(*conv);
	delete conv;
}

s2dpl::Triangle::~Triangle()
{
}