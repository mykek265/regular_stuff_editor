#include "Sensor.h"
#include "../toString.h"
#include <iostream>

//std::vector<s2dpl::Sensor*> s2dpl::Sensor::sensorid;
std::map<std::string ,s2dpl::Sensor*>	s2dpl::Sensor::sensor;
std::vector<std::string>				s2dpl::Sensor::deleted;
b2World*								s2dpl::Sensor::world;
sf::RenderWindow*						s2dpl::Sensor::window;


s2dpl::Sensor::Sensor()
	:contact(0),
	No(0)
{
	std::cout << "Fack!!!" << std::endl;
	//std::string name = "mySensor"+toString(sensor.size());
	//sensor.insert(std::make_pair(name , this));
	//std::cout << bool(sensor["mySensor0"] == this) << std::endl;
}
s2dpl::Sensor::~Sensor()
{
	//линейно меняет номера в списках для других сенсоров
	//удаляет себя из списков
	world->DestroyBody(physics);
	sensor.erase(id);
	if (sensor.size() != No)
		deleted.push_back(id);
}




void s2dpl::Sensor::startContact()
{
	contact++;
	std::cout << "+sensor," << No << '=' << contact << std::endl;
}
void s2dpl::Sensor::endContact()
{
	//if (contact>0)
	contact--;
	std::cout << "-sensor," << No << '=' << contact << std::endl;
}
int s2dpl::Sensor::speak()
{
	return contact;
}
void s2dpl::Sensor::draw()
{
	pos = sf::Vector2f(physics->GetPosition().x*SCALE, -physics->GetPosition().y*SCALE);
	angle = -physics->GetAngle()*RtoG;
	{//отрисовка сенсора
		rectangle.setPosition(pos);
		rectangle.setRotation(angle);
		rectangle.setFillColor(contact <= 0 ? s2dpl::sensorOff : s2dpl::sensorOn);
		window->draw(rectangle);
	}
}
void s2dpl::Sensor::init(b2World& wrld, sf::RenderWindow& wndw)
{
	world = &wrld;
	window = &wndw;
}