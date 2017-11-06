#include "RectSensor.h"
#include <iostream>

//s2dpl::RectSensor::RectSensor(b2World* sworld, sf::RenderWindow* swindow, float x, float y, float w, float h)
//{
//	contact = 0;
//	world = sworld;
//	window = swindow;
//	pos.x = x;
//	pos.y = y;
//	angle = 0.f;
//	sf::RectangleShape* rect = new sf::RectangleShape();
//	rect->setPosition(pos);
//	rect->setSize(sf::Vector2f(w * 2, h * 2));
//	rect->setOrigin(w, h);
//
//	rect->setFillColor(s2dpl::sensorOff);
////создание физического тела сенсора
//	b2BodyDef bdef;
//	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
//	b2PolygonShape shape;
//	b2FixtureDef fdef;
//	shape.SetAsBox(w / s2dpl::SCALE, h / s2dpl::SCALE);
//	fdef.isSensor = true;
//	fdef.shape = &shape;
//	fdef.density = 1.f;
//	bdef.type = b2_staticBody;
//	physics = world->CreateBody(&bdef);
//////////////////запись сенсора в множестве
//	No = id.size();
//	id.push_back("sensor," + toString(sensor.size()));//сохраняем ключ в список
//	sensor.push_back(this);//запоминаем пару
//	//уродливо и по-хамски скармливаем этому баяну ссылку на ключик
//	physics->CreateFixture(&fdef)->SetUserData(static_cast<void*>(&(id[id.size() - 1])));
//	rectangle.push_back(*rect);//запоминаем как должен выглядеть квадрат
//	delete rect;
//
//}
//s2dpl::RectSensor::RectSensor(bool soed, float x, float y, float w, float h)
//{
//	if (window == NULL || world == NULL) throw("Bad initialisation of Sensor! Initialise window and world at first!");
//	contact = 0;
//	pos.x = x;
//	pos.y = y;
//	angle = 0.f;
//	sf::RectangleShape* rect = new sf::RectangleShape();
//	rect->setPosition(pos);
//	rect->setSize(sf::Vector2f(w * 2, h * 2));
//	rect->setOrigin(w, h);
//
//	rect->setFillColor(s2dpl::sensorOff);
//	//создание физического тела сенсора
//	b2BodyDef bdef;
//	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
//	b2PolygonShape shape;
//	b2FixtureDef fdef;
//	shape.SetAsBox(w / s2dpl::SCALE, h / s2dpl::SCALE);
//	fdef.isSensor = true;
//	fdef.shape = &shape;
//	fdef.density = 0.f;
//	bdef.type = soed ? b2_dynamicBody : b2_staticBody;
//	physics = world->CreateBody(&bdef);
//	
//	////////////запись сенсора в списке
//	No = id.size();
//	id.push_back("sensor," + toString(sensor.size()));//сохраняем ключ в список
//	sensor.push_back(this);//запоминаем пару
//
//	physics->CreateFixture(&fdef)->SetUserData(static_cast<void*>(&(id[id.size() - 1])));
//	rectangle.push_back(*rect);
//	delete rect;
//
//}
//s2dpl::RectSensor::RectSensor(b2World* sworld, sf::RenderWindow* swindow, float x, float y, float w, float h, float density)
//{
//	contact = false;
//	world = sworld;
//	window = swindow;
//	pos.x = x;
//	pos.y = y;
//	angle = 0.f;
//	sf::RectangleShape* rect = new sf::RectangleShape();
//	rect->setPosition(pos);
//	rect->setSize(sf::Vector2f(w * 2, h * 2));
//	rect->setOrigin(w, h);
//
//		rect->setFillColor(s2dpl::sensorOff);
////создание физического тела сенсора
//	b2BodyDef bdef;
//	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
//	b2PolygonShape shape;
//	shape.SetAsBox(w / s2dpl::SCALE, h / s2dpl::SCALE);
//	bdef.type = b2_staticBody;
//	physics = world->CreateBody(&bdef);
//////////запись сенсора в списке
//	No = id.size();
//	id.push_back("sensor," + toString(sensor.size()));//сохраняем ключ в список
//	sensor.push_back(this);//запоминаем пару
//
//	physics->CreateFixture(&shape, density)->SetUserData(static_cast<void*>(&(id[id.size() - 1])));
//	rectangle.push_back(*rect);
//	delete rect;
//}
//s2dpl::RectSensor::RectSensor(b2World* sworld, sf::RenderWindow* swindow, float x, float y, float w, float h, float sangle, float density)
//{
//	contact = false;
//	world = sworld;
//	window = swindow;
//	pos.x = x;
//	pos.y = y;
//	angle = sangle;
//	sf::RectangleShape* rect = new sf::RectangleShape();
//	rect->setPosition(pos);
//	rect->setSize(sf::Vector2f(w * 2, h * 2));
//	rect->setOrigin(w, h);
//
//		rect->setFillColor(s2dpl::sensorOff);
//
////создание физического тела сенсора
//	b2BodyDef bdef;
//	bdef.position.Set(x / s2dpl::SCALE, -y / s2dpl::SCALE);
//	bdef.angle = angle;
//	b2PolygonShape shape;
//	shape.SetAsBox(w / s2dpl::SCALE, h / s2dpl::SCALE);
//	bdef.type = b2_staticBody;
//	physics = world->CreateBody(&bdef);
////////////запись сенсора в списке
//	No = id.size();
//	id.push_back("sensor," + toString(sensor.size()));//сохраняем ключ в список
//	sensor.push_back(this);//запоминаем пару
//
////загрузка информации о том на каком месте в списке сенсор искать
//	physics->CreateFixture(&shape, density)->SetUserData(static_cast<void*>(&(id[id.size() - 1])));
//	rectangle.push_back(*rect);
//	delete rect;
//}
s2dpl::RectSensor::RectSensor(bool soed, sf::Vector2f spos, sf::Vector2f size, uint16 dontTouchThat)
{
	std::cout << " Creation of RectSensor:" << std::endl;
	contact = false;
	pos = spos;
	angle = 0.f;
	
	rectangle.setPosition(pos);
	rectangle.setSize(sf::Vector2f(size.x * 2, size.y * 2));
	rectangle.setOrigin(size);
	std::cout << "  sfml rect with position(" << pos.x << ", " << pos.y << ") and size(" << size.x * 2 << ", " << size.y * 2 << ')' << std::endl;

	rectangle.setFillColor(s2dpl::sensorOff);

//создание физического тела сенсора
	b2BodyDef bdef;
	bdef.position.Set(pos.y / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(size.x / s2dpl::SCALE, size.y / s2dpl::SCALE);
	bdef.type = soed ? b2_dynamicBody : b2_staticBody;
	physics = world->CreateBody(&bdef);
	b2FixtureDef fdef;
	fdef.isSensor = true;
	//fdef.filter.maskBits = fdef.filter.maskBits&(!dontTouchThat);
	fdef.shape = &shape;
	fdef.density = .000001f;

	std::cout << "  box2d rect with position(" << pos.x / s2dpl::SCALE << ", " << -pos.y / s2dpl::SCALE << ")[or (" << pos.x << ", " << pos.y << ")]" << std::endl;
	std::cout << "    size("<<size.x/s2dpl::SCALE<<", "<<size.y/s2dpl::SCALE<<")[or ("<<size.x*2.f<<", "<<size.y*2.f<<")]" << std::endl;
//запись сенсора в списке
	No = sensor.size();
	id="sensor," + toString(No);//сохраняем ключ в список
	sensor.insert(std::make_pair(id, this));//запоминаем пару
	//std::cout << "  No=" << No << ";  push in id-list->" << *(id.end() - 1) << ";  push in sensor-list->" << this;

//загрузка информации о том на каком месте в списке сенсор искать
	physics->CreateFixture(&fdef)->SetUserData(static_cast<void*>(&(id)));
	//std::cout << "  setting user data link on as id[id.size-1]==\"" << id[id.size - 1] << "\"; &(id[id.size-1])=" << &(id[id.size - 1]) << std::endl;
	rectangle;
	std::cout << "  id-std::string = \"" << id << "\"" << std::endl;
	std::cout << "  current sizes of\n    sensor-list=" << sensor.size() << std::endl;
}
s2dpl::RectSensor::RectSensor(sf::Vector2f spos, sf::Vector2f size, float density)
{
	contact = false;
	pos = spos;
	angle = 0.f;
	rectangle.setPosition(pos);
	rectangle.setSize(sf::Vector2f(size.x * 2, size.y * 2));
	rectangle.setOrigin(size);

	rectangle.setFillColor(s2dpl::sensorOff);

//создание физического тела сенсора
	b2BodyDef bdef;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	b2PolygonShape shape;
	shape.SetAsBox(size.x / s2dpl::SCALE, size.y / s2dpl::SCALE);
	bdef.type = b2_staticBody;
	physics = world->CreateBody(&bdef);
//запись сенсора в списке
	if (deleted.empty())
	{
		id = "sensor,";
		id+=toString(sensor.size());//сохраняем ключ в список
		No = sensor.size();
	}
	else
	{
		id = deleted[deleted.size()-1];
		deleted.erase(deleted.end() - 1);
	}
	sensor.insert(std::make_pair(id, this));//запоминаем пару

//загрузка информации о том на каком месте в списке сенсор искать
	physics->CreateFixture(&shape, density)->SetUserData(static_cast<void*>(&(id)));
}
s2dpl::RectSensor::RectSensor(sf::Vector2f spos, sf::Vector2f size, float density, float sangle)
{
	contact = false;
	pos = spos;
	angle = sangle;
	rectangle.setPosition(pos);
	rectangle.setSize(sf::Vector2f(size.x * 2, size.y * 2));
	rectangle.setOrigin(size);

	rectangle.setFillColor(s2dpl::sensorOff);

//создание физического тела сенсора
	b2BodyDef bdef;
	bdef.position.Set(pos.x / s2dpl::SCALE, -pos.y / s2dpl::SCALE);
	bdef.angle = angle;
	b2PolygonShape shape;
	shape.SetAsBox(size.x / s2dpl::SCALE, size.y / s2dpl::SCALE);
	bdef.type = b2_staticBody;
	physics = world->CreateBody(&bdef);
//запись сенсора в списке
	No = sensor.size();
	id="sensor," + toString(sensor.size());//сохраняем ключ в список
	sensor.insert(std::make_pair(id,this));//запоминаем пару

//загрузка информации о том на каком месте в списке сенсор искать
	physics->CreateFixture(&shape, density)->SetUserData(static_cast<void*>(&(id)));
}


s2dpl::RectSensor::~RectSensor()
{
	std::cout << "AAAAA! FUCK!!!!" << std::endl;
}