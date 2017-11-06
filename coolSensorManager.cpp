#include "coolSensorManager.h"
#include "CoolMenu.h"
#include "windowSize.h"
#include <iostream>
std::vector<PrimitivBluePr>*coolSensorManager::bpr(nullptr);
sf::Vector2f				coolSensorManager::sdvig;
sf::Vector2f				coolSensorManager::mouse;
bool						coolSensorManager::ch(false);
sf::RectangleShape			coolSensorManager::line;
sf::RectangleShape			coolSensorManager::rect;
PrimitivBluePr*				coolSensorManager::curPrm;


coolSensorManager::coolSensorManager()
	:bwp(false),
	countP(0)
{
	rect.setFillColor(sf::Color(255, 255, 148, 105));
	line.setFillColor(sf::Color(255, 255, 148, 55));
}


coolSensorManager::~coolSensorManager()
{}

void coolSensorManager::draw()
{
	zoom = SensorBpr::window->getView().getSize().x / WIDTH;
	sdvig = -sf::Vector2f(SensorBpr::window->getSize())*0.5f*zoom + SensorBpr::window->getView().getCenter();
	mouse = sf::Vector2f(sf::Mouse::getPosition(*SensorBpr::window))*zoom + sdvig;
	sf::Vector2f v;
	float r;
	//-----------------------------------------------------------------
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !bwp)
	//{
	//	bwp = true;
	//	countP++;
	//}
	//-----------------------------------------------------------------
	if (countP == 0 && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !bwp)
	{
		std::for_each(ppr->begin(), ppr->end(), [](PrimitivBluePr& pr)
		{
			sf::Vector2f v = pr.getPosition() - mouse;
			float r = std::sqrtf(v.x*v.x + v.y*v.y);
			if (r < 20)
			{
				curPrm = &pr;
				line.setPosition(pr.getPosition());
				ch = true;
			}
		});
		if (ch)
		{
			bwp = true;
			countP++;
		}
	}
	//-----------------------------------------------------------------
	if (countP == 2)
	{
		v = mouse - line.getPosition();
		r = std::sqrtf(v.x*v.x + v.y*v.y);
		line.setSize({ r, 2 });
		line.setRotation(std::atan2f(v.y, v.x)*s2dpl::RtoG);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !bwp)
		{
			rect.setPosition(mouse);
			bwp = true;
			countP++;
		}
	}
	//-----------------------------------------------------------------
	if (countP == 4)
	{
		v = mouse - rect.getPosition();
		rect.setSize({ std::abs(v.x*2.f), std::abs(v.y*2.f) });
		rect.setOrigin(rect.getSize()*0.5f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !bwp)
		{

			SensorBpr sen(rect.getSize(), rect.getPosition() - line.getPosition());//размер, позиция, к какой фигуре прикрепить
			curPrm->addSensor(sen);
			
			CoolMenu::state = 0;
			CoolMenu::setZeroState();
			curPrm = nullptr;
			bwp = true;
			countP = -1;
			ch = false;
			rect.setSize({ 0, 0 });
			line.setSize({ 0, 0 });
		}
	}
	//-----------------------------------------------------------------
	if (countP != 0 || countP != 2 || countP != 4)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right) && bwp)
		{
			bwp = false;
			countP++;
		}
	}
	SensorBpr::window->draw(line);
	SensorBpr::window->draw(rect);
}