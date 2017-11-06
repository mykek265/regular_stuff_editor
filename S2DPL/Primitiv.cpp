#include "Primitiv.h"
#include <iostream>
#include <vector>
sf::RenderWindow*	s2dpl::Primitiv::window = NULL;
b2World*			s2dpl::Primitiv::world = NULL;


s2dpl::Primitiv::Primitiv(){
}
s2dpl::Primitiv::Primitiv(b2World& sworld, sf::RenderWindow& swindow, const sf::Vector2f& spos, int type)
	:pos(spos),
	angle(0.f),
	im(0xFFFF),
	iColWth(0xFFFF)
{
	window = &swindow;
	world = &sworld;
	b2BodyDef bdef;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	if (type == 1)
		bdef.type = b2_dynamicBody;
	if (type == 2)
		bdef.type = b2_kinematicBody;

	physics = world->CreateBody(&bdef);
}
s2dpl::Primitiv::Primitiv(b2World& sworld, sf::RenderWindow& swindow, const sf::Vector2f& spos, float density, float friction, float elasticity, int type, const uint16& rim, const uint16& ricol)
	:pos(spos),
	angle(0.f),
	im(rim),
	iColWth(ricol)
{
	window = &swindow;
	world = &sworld;
	b2BodyDef bdef;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	if (type == 1)
		bdef.type = b2_dynamicBody;
	if (type == 2)
		bdef.type = b2_kinematicBody;

	physics = world->CreateBody(&bdef);
}
void s2dpl::Primitiv::draw()
{
	pos = sf::Vector2f(physics->GetPosition().x*SCALE, -physics->GetPosition().y*SCALE);
	angle = -physics->GetAngle()*RtoG;
	if (true)//если режим отладочный
	{
		int i=0, size = rectangle.size();
		while (i != size)
		{
			rectangle[i].setPosition(pos);
			rectangle[i].setRotation(angle);
			window->draw(rectangle[i]);
			i++;
		}
		i = 0;
		size = circle.size();
		while (i != size)
		{
			circle[i].setPosition(pos);
			circle[i].setRotation(angle);
			window->draw(circle[i]);
			i++;
		}
		i = 0;
		size = triangle.size();
		while (i != size)
		{
			triangle[i].setPosition(pos);
			triangle[i].setRotation(angle);
			window->draw(triangle[i]);
			i++;
		}
		std::for_each(ptrSensor.begin(), ptrSensor.end(), [](s2dpl::Sensor* s){ s->draw(); });
	}
	int i = 0;
	int size = sprite.size();
	while (i != size)
	{
		sprite[i].setPosition(pos);
		sprite[i].rotate(angle);
		window->draw(sprite[i]);
		sprite[i].rotate(-angle);
		i++;
	}
}
s2dpl::Primitiv::~Primitiv()
{
	rectangle.clear();
	circle.clear();
	triangle.clear();
	
	std::for_each(jj.begin(), jj.end(), [](b2Joint*j){ world->DestroyJoint(j); });//вначале выпиливаем соединение, потом
	jj.clear();
	std::for_each(ptrSensor.begin(), ptrSensor.end(), [](s2dpl::Sensor* s){ delete s; });
	ptrSensor.clear();//даём умным ссылкам вызвать деструкторы сенсоров, а потом,
	world->DestroyBody(physics);//убираем тело, к которому они были прикреплены
}


///////////////////////////////////////////////////
//---------Добавление форм и сенсоров--------------

////-------------------------------------------------
//void s2dpl::Primitiv::addRect(float ox, float oy, float w, float h)
//{
//	sf::RectangleShape* rect = new sf::RectangleShape();
//	rect->setSize(sf::Vector2f(std::abs(w) * 2, std::abs(h) * 2));
//	rect->setFillColor(stat);
//	rect->setOrigin(std::abs(w) - ox, std::abs(h) - oy);
//
//	if (physics->GetType() == b2_kinematicBody)
//		rect->setFillColor(kinem);
//	if (physics->GetType() == b2_dynamicBody)
//		rect->setFillColor(dynam);
//	rectangle.push_back(*rect);
//	delete rect;
//	b2PolygonShape boxsh;
//	boxsh.SetAsBox(std::abs(w) / SCALE, std::abs(h) / SCALE, b2Vec2(ox / SCALE, -oy / SCALE), 0);
//	physics->CreateFixture(&boxsh, 1.f);
//}
//void s2dpl::Primitiv::addRect(float ox, float oy, float w, float h, float density)
//{
//	sf::RectangleShape* rect = new sf::RectangleShape();
//	rect->setSize(sf::Vector2f(std::abs(w) * 2, std::abs(h) * 2));
//	rect->setFillColor(stat);
//	rect->setOrigin(std::abs(w) - ox, std::abs(h) - oy);
//
//	if (physics->GetType() == b2_kinematicBody){
//		rect->setFillColor(kinem);
//	}
//	if (physics->GetType() == b2_dynamicBody){
//		rect->setFillColor(dynam);
//	}
//	rectangle.push_back(*rect);
//	delete rect;
//	b2PolygonShape boxsh;
//	boxsh.SetAsBox(std::abs(w) / SCALE, std::abs(h) / SCALE, b2Vec2(ox / SCALE, -oy / SCALE), 0);
//	physics->CreateFixture(&boxsh, density);
//}
//void s2dpl::Primitiv::addRect(float ox, float oy, float w, float h, float density, float elasticity, float friction)
//{
//	sf::RectangleShape* rect = new sf::RectangleShape();
//	rect->setSize(sf::Vector2f(std::abs(w) * 2, std::abs(h) * 2));
//	rect->setFillColor(stat);
//	rect->setOrigin(std::abs(w) - ox, std::abs(h) - oy);
//
//	if (physics->GetType() == b2_kinematicBody){
//		rect->setFillColor(kinem);
//	}
//	if (physics->GetType() == b2_dynamicBody){
//		rect->setFillColor(dynam);
//	}
//	rectangle.push_back(*rect);
//	delete rect;
//	b2PolygonShape boxsh;
//	boxsh.SetAsBox(std::abs(w) / SCALE, std::abs(h) / SCALE, b2Vec2(ox / SCALE, -oy / SCALE), 0);
//	b2FixtureDef fdef;
//	fdef.density = density;
//	fdef.friction = friction;
//	fdef.restitution = elasticity;
//	fdef.shape = &boxsh;
//	physics->CreateFixture(&fdef);
//}
////-----------------------------------
//void s2dpl::Primitiv::addCirc(float ox, float oy, float r)
//{
//	sf::CircleShape* circ = new sf::CircleShape(r);
//	circ->setOrigin(r - ox, r - oy);
//	circ->setFillColor(stat);
//
//	if (physics->GetType() == b2_kinematicBody){
//		circ->setFillColor(kinem);
//	}
//	if (physics->GetType() == b2_dynamicBody){
//		circ->setFillColor(dynam);
//	}
//	circle.push_back(*circ);
//	delete circ;
//	b2CircleShape cirsh;
//	cirsh.m_radius = r / SCALE;
//	cirsh.m_p = b2Vec2(ox / SCALE, -oy / SCALE);
//	physics->CreateFixture(&cirsh, 1.f);
//}
//void s2dpl::Primitiv::addCirc(float ox, float oy, float r, float density)
//{
//	sf::CircleShape* circ = new sf::CircleShape(r);
//	circ->setOrigin(r - ox, r - oy);
//	circ->setFillColor(stat);
//
//	if (physics->GetType() == b2_kinematicBody){
//		circ->setFillColor(kinem);
//	}
//	if (physics->GetType() == b2_dynamicBody){
//		circ->setFillColor(dynam);
//	}
//	circle.push_back(*circ);
//	delete circ;
//	b2CircleShape cirsh;
//	cirsh.m_radius = r / SCALE;
//	cirsh.m_p = b2Vec2(ox / SCALE, -oy / SCALE);
//	physics->CreateFixture(&cirsh, density);
//}
//void s2dpl::Primitiv::addCirc(float ox, float oy, float r, float density, float elasticity, float friction)
//{
//	sf::CircleShape* circ = new sf::CircleShape(r);
//	circ->setOrigin(r - ox, r - oy);
//	circ->setFillColor(stat);
//
//	if (physics->GetType() == b2_kinematicBody){
//		circ->setFillColor(kinem);
//	}
//	if (physics->GetType() == b2_dynamicBody){
//		circ->setFillColor(dynam);
//	}
//	circle.push_back(*circ);
//	delete circ;
//	b2CircleShape cirsh;
//	cirsh.m_radius = r / SCALE;
//	cirsh.m_p = b2Vec2(ox / SCALE, -oy / SCALE);
//	b2FixtureDef fdef;
//	fdef.density = density;
//	fdef.friction = friction;
//	fdef.restitution = elasticity;
//	fdef.shape = &cirsh;
//	physics->CreateFixture(&fdef);
//}
////-----------------------------------
//void s2dpl::Primitiv::addTriang(float ox, float oy, sf::Vector2f v3[])
//{
//	sf::ConvexShape* conv = new sf::ConvexShape();
//	//s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
//	conv->setPointCount(3);
//	for (int i = 0; i < 3; i++)
//		conv->setPoint(i, *(v3 + i));
//	conv->setFillColor(stat);
//
//	if (physics->GetType() == b2_kinematicBody)
//		conv->setFillColor(kinem);
//	if (physics->GetType() == b2_dynamicBody)
//		conv->setFillColor(dynam);
//
//	triangle.push_back(*conv);
//	delete conv;
//	b2PolygonShape convsh;
//	b2Vec2 vertices[3];
//	v3[0] += sf::Vector2f(ox, oy);
//	v3[1] += sf::Vector2f(ox, oy);
//	v3[2] += sf::Vector2f(ox, oy);
//	vertices[0].Set(v3[0].x / SCALE, -v3[0].y / SCALE);
//	vertices[1].Set(v3[1].x / SCALE, -v3[1].y / SCALE);
//	vertices[2].Set(v3[2].x / SCALE, -v3[2].y / SCALE);
//	convsh.Set(vertices, 3);
//	physics->CreateFixture(&convsh, 1);
//}
//void s2dpl::Primitiv::addTriang(float ox, float oy, sf::Vector2f v3[], float density)
//{
//	sf::ConvexShape* conv = new sf::ConvexShape();
//	//s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
//	conv->setPointCount(3);
//	for (int i = 0; i < 3; i++)
//		conv->setPoint(i, *(v3 + i));
//	conv->setFillColor(stat);
//
//	if (physics->GetType() == b2_kinematicBody)
//		conv->setFillColor(kinem);
//	if (physics->GetType() == b2_dynamicBody)
//		conv->setFillColor(dynam);
//
//	triangle.push_back(*conv);
//	delete conv;
//	b2PolygonShape convsh;
//	b2Vec2 vertices[3];
//	v3[0] += sf::Vector2f(ox, oy);
//	v3[1] += sf::Vector2f(ox, oy);
//	v3[2] += sf::Vector2f(ox, oy);
//	vertices[0].Set(v3[0].x / SCALE, -v3[0].y / SCALE);
//	vertices[1].Set(v3[1].x / SCALE, -v3[1].y / SCALE);
//	vertices[2].Set(v3[2].x / SCALE, -v3[2].y / SCALE);
//	convsh.Set(vertices, 3);
//	physics->CreateFixture(&convsh, density);
//}
//void s2dpl::Primitiv::addTriang(float ox, float oy, sf::Vector2f v3[], float density, float elasticity, float friction)
//{
//	sf::ConvexShape* conv = new sf::ConvexShape();
//	//s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
//	conv->setPointCount(3);
//	for (int i = 0; i < 3; i++)
//		conv->setPoint(i, *(v3 + i));
//	conv->setFillColor(stat);
//
//	if (physics->GetType() == b2_kinematicBody)
//		conv->setFillColor(kinem);
//	if (physics->GetType() == b2_dynamicBody)
//		conv->setFillColor(dynam);
//
//	triangle.push_back(*conv);
//	delete conv;
//	b2PolygonShape convsh;
//	b2Vec2 vertices[3];
//	v3[0] += sf::Vector2f(ox, oy);
//	v3[1] += sf::Vector2f(ox, oy);
//	v3[2] += sf::Vector2f(ox, oy);
//	vertices[0].Set(v3[0].x / SCALE, -v3[0].y / SCALE);
//	vertices[1].Set(v3[1].x / SCALE, -v3[1].y / SCALE);
//	vertices[2].Set(v3[2].x / SCALE, -v3[2].y / SCALE);
//	convsh.Set(vertices, 3);
//	b2FixtureDef fdef;
//	fdef.density = density;
//	fdef.friction = friction;
//	fdef.restitution = elasticity;
//	fdef.shape = &convsh;
//	physics->CreateFixture(&fdef);
//}
//////////////////////////////////////////

void s2dpl::Primitiv::addRect(sf::Vector2f pos, sf::Vector2f size)
{
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setSize(sf::Vector2f(std::abs(size.x) * 2, std::abs(size.y) * 2));
	rect->setOrigin(std::abs(size.x) - pos.x, std::abs(size.y) - pos.y);

	setColor(physics->GetType(), rect);
	rectangle.push_back(*rect);
	delete rect;
	b2PolygonShape boxsh;
	boxsh.SetAsBox(std::abs(size.x) / SCALE, std::abs(size.y) / SCALE, b2Vec2(pos.x / SCALE, -pos.y / SCALE), 0);
	physics->CreateFixture(&boxsh, 1.f);
}
void s2dpl::Primitiv::addRect(sf::Vector2f pos, sf::Vector2f size, float density)
{
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setSize(sf::Vector2f(std::abs(size.x) * 2, std::abs(size.y) * 2));
	rect->setOrigin(std::abs(size.x) - pos.x, std::abs(size.y) - pos.y);

	setColor(physics->GetType(), rect);
	rectangle.push_back(*rect);
	delete rect;
	b2PolygonShape boxsh;
	boxsh.SetAsBox(std::abs(size.x) / SCALE, std::abs(size.y) / SCALE, b2Vec2(pos.x / SCALE, -pos.y / SCALE), 0);
	physics->CreateFixture(&boxsh, density);
}
void s2dpl::Primitiv::addRect(sf::Vector2f pos, sf::Vector2f size, float density, float friction, float elasticity)
{
	sf::RectangleShape* rect = new sf::RectangleShape();
	rect->setSize(sf::Vector2f(std::abs(size.x) * 2, std::abs(size.y) * 2));
	rect->setOrigin(std::abs(size.x) - pos.x, std::abs(size.y) - pos.y);

	setColor(physics->GetType(), rect);
	rectangle.push_back(*rect);
	delete rect;
	b2PolygonShape boxsh;
	boxsh.SetAsBox(std::abs(size.x) / SCALE, std::abs(size.y) / SCALE, b2Vec2(pos.x / SCALE, -pos.y / SCALE), 0);
	b2FixtureDef fdef;
	fdef.density = density;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	fdef.filter.categoryBits = im;
	fdef.filter.maskBits = iColWth;
	fdef.shape = &boxsh;
	physics->CreateFixture(&fdef);
}
//-----------------------------------
void s2dpl::Primitiv::addCirc(sf::Vector2f pos, float r)
{
	sf::CircleShape* circ = new sf::CircleShape(r);
	circ->setOrigin(r - pos.x, r - pos.y);

	setColor(physics->GetType(), circ);
	circle.push_back(*circ);
	delete circ;
	b2CircleShape cirsh;
	cirsh.m_radius = r / SCALE;
	cirsh.m_p = b2Vec2(pos.x / SCALE, -pos.y / SCALE);
	physics->CreateFixture(&cirsh, 1.f);
}
void s2dpl::Primitiv::addCirc(sf::Vector2f pos, float r, float density)
{
	sf::CircleShape* circ = new sf::CircleShape(r);
	circ->setOrigin(r - pos.x, r - pos.y);

	setColor(physics->GetType(), circ);
	circle.push_back(*circ);
	delete circ;
	b2CircleShape cirsh;
	cirsh.m_radius = r / SCALE;
	cirsh.m_p = b2Vec2(pos.x / SCALE, -pos.y / SCALE);
	physics->CreateFixture(&cirsh, density);
}
void s2dpl::Primitiv::addCirc(sf::Vector2f pos, float r, float density, float friction, float elasticity)
{
	sf::CircleShape* circ = new sf::CircleShape(r);
	circ->setOrigin(r - pos.x, r - pos.y);

	setColor(physics->GetType(), circ);
	circle.push_back(*circ);
	delete circ;
	b2CircleShape cirsh;
	cirsh.m_radius = r / SCALE;
	cirsh.m_p = b2Vec2(pos.x / SCALE, -pos.y / SCALE);
	b2FixtureDef fdef;
	fdef.density = density;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	fdef.filter.categoryBits = im;
	fdef.filter.maskBits = iColWth;
	fdef.shape = &cirsh;
	physics->CreateFixture(&fdef);
}
//-----------------------------------
void s2dpl::Primitiv::addTriang(sf::Vector2f& ppos, sf::Vector2f v3[])
{
	sf::ConvexShape* conv = new sf::ConvexShape();
	//s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
	conv->setPointCount(3);
	for (int i = 0; i < 3; i++)
		conv->setPoint(i, *(v3 + i));
	conv->setOrigin(-ppos);


	setColor(physics->GetType(), conv);
	triangle.push_back(*conv);
	delete conv;
	b2PolygonShape convsh;
	b2Vec2 vertices[3];
	v3[0] += ppos;
	v3[1] += ppos;
	v3[2] += ppos;
	vertices[0].Set(v3[0].x / s2dpl::SCALE, -v3[0].y / s2dpl::SCALE);
	vertices[1].Set(v3[1].x / s2dpl::SCALE, -v3[1].y / s2dpl::SCALE);
	vertices[2].Set(v3[2].x / s2dpl::SCALE, -v3[2].y / s2dpl::SCALE);
	convsh.Set(vertices, 3);

	physics->CreateFixture(&convsh, 1);
}
void s2dpl::Primitiv::addTriang(sf::Vector2f pos, sf::Vector2f v3[], float density)
{
	sf::ConvexShape* conv = new sf::ConvexShape();
	//s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
	conv->setPointCount(3);
	for (int i = 0; i < 3; i++)
		conv->setPoint(i, *(v3 + i));


	setColor(physics->GetType(), conv);
	triangle.push_back(*conv);
	delete conv;
	b2PolygonShape convsh;
	b2Vec2 vertices[3];
	v3[0] += pos;
	v3[1] += pos;
	v3[2] += pos;
	vertices[0].Set(v3[0].x / SCALE, -v3[0].y / SCALE);
	vertices[1].Set(v3[1].x / SCALE, -v3[1].y / SCALE);
	vertices[2].Set(v3[2].x / SCALE, -v3[2].y / SCALE);
	convsh.Set(vertices, 3);
	physics->CreateFixture(&convsh, density);
}
void s2dpl::Primitiv::addTriang(sf::Vector2f pos, sf::Vector2f v3[], float density, float friction, float elasticity)
{
	sf::ConvexShape* conv = new sf::ConvexShape();
	//s2dpl::Primitiv::juggleV(v3, v3 + 1, v3 + 2);
	conv->setPointCount(3);
	for (int i = 0; i < 3; i++)
		conv->setPoint(i, *(v3 + i));

	setColor(physics->GetType(), conv);
	triangle.push_back(*conv);
	delete conv;
	b2PolygonShape convsh;
	b2Vec2 vertices[3];
	v3[0] += pos;
	v3[1] += pos;
	v3[2] += pos;
	vertices[0].Set(v3[0].x / SCALE, -v3[0].y / SCALE);
	vertices[1].Set(v3[1].x / SCALE, -v3[1].y / SCALE);
	vertices[2].Set(v3[2].x / SCALE, -v3[2].y / SCALE);
	convsh.Set(vertices, 3);
	b2FixtureDef fdef;
	fdef.density = density;
	fdef.friction = friction;
	fdef.restitution = elasticity;
	fdef.filter.categoryBits = im;
	fdef.filter.maskBits = iColWth;
	fdef.shape = &convsh;
	physics->CreateFixture(&fdef);
}
//////////////////////////////////////////
void s2dpl::Primitiv::addImg(sf::Sprite spr)
{
	sprite.push_back(spr);
}
//----------------------------------------------
s2dpl::Sensor* s2dpl::Primitiv::addSensor(sf::Vector2f spos, sf::Vector2f size)
{
	std::cout << "Adding a Sensor!" << std::endl;
	
	s2dpl::Sensor* a = new s2dpl::RectSensor(true, { pos.x + spos.x, pos.y + spos.y }, { size.x, size.y }, uint16(0x0000));
	
	b2RevoluteJointDef jdef;
	{
	jdef.enableLimit = true;
		jdef.lowerAngle = 0.f;
		jdef.upperAngle = 0.f + s2dpl::GtoR;
	jdef.bodyA = this->physics;
	}
	ptrSensor.push_back(a);
	jdef.bodyB = a->physics;//сохраняется в векторе sensorid, так что тут нет криминал
	jdef.localAnchorA = b2Vec2(spos.x / s2dpl::SCALE, -spos.y / s2dpl::SCALE);
	jdef.localAnchorB = b2Vec2_zero;
	jdef.collideConnected = false;
	jj.push_back(world->CreateJoint(&jdef));//запоминаем соединение
	return a;
}
//-----------------------------------


void s2dpl::Primitiv::juggleV(sf::Vector2f* A, sf::Vector2f* B, sf::Vector2f* C)
{
	float x = A->x, y = A->y, a = B->x, b = B->y, c = C->x, d = C->y;
	if (x >= c && x >= a && a >= c && b >= d && y <= b){
		*B = { c, d }; *C = { a, b };
	}
	else if (c >= a && c >= x && x >= a && y >= b && d <= y){
		*A = { c, d }; *B = { a, b }; *C = { x, y };
	}
	else if (c >= x && c >= a && a >= x && b >= y && d <= b){
		*A = { c, d }; *B = { x, y }; *C = { a, b };
	}
	else if (a >= c && a >= x && c >= x && d >= y && b <= d){
		*A = { a, b }; *B = { x, y }; *C = { c, d };
	}
	else if (a >= c && a >= x && x >= c && y >= d && b <= y){
		*A = { a, b }; *B = { c, d }; *C = { x, y };
	}
}

