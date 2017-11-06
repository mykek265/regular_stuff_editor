#include "SensorBpr.h"
#include "S2DPL\s2dplDefenitions.h"
#include <iostream>
sf::RenderWindow* SensorBpr::window;
sf::Vector2f SensorBpr::vec(0,0);


SensorBpr::SensorBpr()
{
	shape.setFillColor(sf::Color(255, 255, 148, 105));
	shape.setOutlineThickness(1);
	center.setRadius(3.f);
	center.setOrigin(3.f, 3.f);
	center.setFillColor(sf::Color(255, 0, 148, 155));
	line.setFillColor(sf::Color(255, 255, 148, 105));
}

SensorBpr::SensorBpr(const sf::Vector2f& size, const sf::Vector2f& pos)
{
	shape.setFillColor(sf::Color(255, 255, 148, 105));
	shape.setOutlineThickness(1);
	shape.setSize(size);
	shape.setOrigin(size*0.5f);
	shape.setPosition(pos);
	center.setRadius(3.f);
	center.setOrigin(3.f, 3.f);
	center.setFillColor(sf::Color(255, 0, 148, 155));
	line.setFillColor(sf::Color(255, 255, 148, 105));
}

SensorBpr::~SensorBpr()
{
}

void SensorBpr::draw(const sf::Vector2f& pos)
{
	center.setPosition(pos + shape.getPosition());
	vec = center.getPosition() - line.getPosition();
	line.setPosition(pos);//если таковой сместился
	 
	line.setSize(sf::Vector2f(std::sqrtf(vec.x * vec.x + vec.y * vec.y), 2.f ));
	//std::cout << "Line!!!:" << line.getSize().x << ',' << line.getSize().y << std::endl;
	line.setRotation( std::atan2f(vec.y, vec.x) * s2dpl::RtoG );
	//std::cout << "Line:" << line.getSize().x << ',' << line.getSize().y << std::endl;
	window->draw(line);
	//std::cout << "shapeAAAA" << std::endl;
	shape.move(pos);
	window->draw(shape);
	shape.move(-pos);
	window->draw(center);
}

sf::Vector2f SensorBpr::getSize()
{
	return sf::Vector2f(std::abs(shape.getSize().x), std::abs(shape.getSize().y))*0.5f;
}

sf::Vector2f SensorBpr::getPosition()
{
	return shape.getPosition();
}