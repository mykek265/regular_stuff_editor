#include "PrimitivBluePr.h"
#include "windowSize.h"
#include <iostream>
//-----------------------------------------------------------
sf::Vector2f		PrimitivBluePr::sdvig(0, 0);
sf::Vector2f		PrimitivBluePr::podsdvig(0, 0);
sf::Vector2f		PrimitivBluePr::mouse(0, 0);
sf::RenderWindow*	PrimitivBluePr::window;
int					PrimitivBluePr::size(0);
PrimitivBluePr*		PrimitivBluePr::chosen = NULL;
sf::Text			PrimitivBluePr::characteristics;
bool				PrimitivBluePr::dontTouchThat(false);
//-----------------------------------------------------------
void sortVOfTriang(sf::ConvexShape& conv)
{
	sf::Vector2f v2[3] = { { conv.getPoint(0) }, { conv.getPoint(1) }, { conv.getPoint(2) } };

	std::cout << "Conv.getOrigin1: " << conv.getOrigin().x <<','<< conv.getOrigin().y << std::endl;
	for (int i = 0; i < 3; i++)
		conv.setPoint(i, v2[i] + conv.getPosition());
	conv.setOrigin(-conv.getPosition());
	conv.setPosition(0.f, 0.f);

	sf::Vector2f truePos((v2[0].x + v2[1].x + v2[2].x) / 3.f, (v2[0].y + v2[1].y + v2[2].y) / 3.f);

	sf::Vector2f trv[3] = { { v2[0] - truePos }, { v2[1] - truePos }, { v2[2] - truePos } };
	float a1[3] = { std::atan2f(trv[0].y, trv[0].x), std::atan2f(trv[1].y, trv[1].x), std::atan2f(trv[2].y, trv[2].x) };
	float a2[3] = { a1[0], a1[1], a1[2] };
	std::sort(a2, a2 + 3);
	std::swap(a2[0], a2[2]);
	//float a3[3] = { a2[2], a2[1], a2[0] };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (a1[i] == a2[j]) conv.setPoint(j, trv[i]);

	conv.setPosition(truePos);

	//for (int i = 0; i < 3; i++)
	//	std::cout << "a" << i << " : " << conv.getPoint(i).x << ',' << conv.getPoint(i).y << std::endl;

	std::cout << "Conv: " << conv.getPosition().x << ',' << conv.getPosition().y << std::endl;
	for (int i = 0; i < 3; i++)
		std::cout << "point " << i << ": " << conv.getPoint(i).x << ',' << conv.getPoint(i).y << std::endl;
	std::cout << "Conv.getOrigin2: " << conv.getOrigin().x << ',' << conv.getOrigin().y << std::endl;
	
}
void PrimitivBluePr::characteristicStringSetter(const sf::Vector2f& pos)
{
	characteristics.setString(
		"Position:(" + toString(pos.x) + ", " + toString(pos.y) + ")\n" +
		"R: " + toString(rect.size()) + ", C: " + toString(circle.size()) + ", T: " + toString(triang.size()) + "\n" +
		"type: " + (type==0?"Static":(type==2?"Dynamic":"Kinematic")) + ", density: " + toString(density) + ", friction: " + toString(friction) +
		", elasticity:" + toString(elasticity) + mask
		);
}
/////////////////////////////////////////////////////////////
PrimitivBluePr::PrimitivBluePr()
	:type(0),
	density(1.f),
	friction(.3f),
	checked(false),
	loaded(false),
	sn(0),
	st(0)
{
	for (int i = 0; i < 16; i++)
	{
		im[i] = false;
		colWith[i] = false;
	}
	size++; //учёт
}
PrimitivBluePr::PrimitivBluePr(sf::RenderWindow& w, CoolFigureEditor& cfe, CoolFeatureWindow& cfw)
	:type(cfw.type),
	density(cfw.density),
	friction(cfw.friction),
	elasticity(cfw.elasticity),
	checked(false),
	loaded(false),
	sn(0),
	st(0)
{
	rect = cfe.rect;
	circle = cfe.circle;
	triang = cfe.triangle;
	sf::Vector2f p = cfe.center.getPosition();
	window = &w;
	center.setFillColor(sf::Color(68, 219, 30, 150));
	for (unsigned int i = 0; i < rect.size(); i++)
	{
		rect[i].setFillColor(sf::Color(0, 97, 255, 150));
		rect[i].setOutlineThickness(1);
		rect[i].move(-p);
	}
	for (unsigned int i = 0; i < circle.size(); i++)
	{
		circle[i].setFillColor(sf::Color(0, 97, 255, 150));
		circle[i].setOutlineThickness(1);
		circle[i].move(-p);
	}
	std::cout << "Center: " << p.x << ',' << p.y << std::endl;
	for (unsigned int i = 0; i < triang.size(); i++)
	{
		triang[i].setFillColor(sf::Color(0, 97, 255, 150));
		triang[i].setOutlineThickness(1);
		triang[i].move(-p);
		sortVOfTriang(triang[i]);
	}
	std::string mask1 = "\n_I'm", mask2 = "\nThm";
	for (int i = 0; i < 16; i++)
	{
		im[i] = cfw.im[i];
		colWith[i] = cfw.icolwith[i];
		mask1 += ((im[i] * (i + 1) < 10) ? "[0" : "[") + toString(im[i] * (i + 1));
		mask2 += ((colWith[i] * (i + 1) < 10) ? "[0" : "[") + toString(colWith[i] * (i + 1));
	}
	mask = mask1 + mask2;
	center.setPosition(p);
	if (rect.size() == 1 && circle.empty() && triang.empty())
		rect.begin()->setPosition(-rect.begin()->getSize() * 0.5f);
	if (rect.empty() && circle.size() == 1 && triang.empty())
		circle.begin()->setPosition(0, 0);
	if (rect.empty() && circle.empty() && triang.size() == 1)
		triang.begin()->setPosition(p);

	center.setRadius(5);
	center.setOrigin(5, 5);
	center.setOutlineThickness(1);

	cfe.rect.clear();//уборка
	cfe.circle.clear();
	cfe.triangle.clear();
	size++;//учёт
}
PrimitivBluePr::~PrimitivBluePr()
{
	size--;//учёт
}
//-----------------------------------------------------------
std::vector<sf::RectangleShape>& PrimitivBluePr::getRects()
{
	return rect;
}
std::vector<sf::CircleShape>&	 PrimitivBluePr::getCircles()
{
	return circle;
}
std::vector<sf::ConvexShape>&	 PrimitivBluePr::getTriangles()
{
	return triang;
}
int								 PrimitivBluePr::getType()
{
	return type;
}
sf::Vector2f					 PrimitivBluePr::getCenter()
{
	return center.getPosition();
}
sf::Vector2f					 PrimitivBluePr::getPosition()
{
	return center.getPosition();
}
std::vector<sf::Sprite>*		 PrimitivBluePr::getImages()
{
	return &sprite;
}
uint16							 boolvToMask(bool v[])
{
	uint16 mask(0x0000);
	mask = mask | (v[0] ? 0x0001 : 0x0000);
	mask = mask | (v[1] ? 0x0002 : 0x0000);
	mask = mask | (v[2] ? 0x0004 : 0x0000);
	mask = mask | (v[3] ? 0x0008 : 0x0000);
	mask = mask | (v[4] ? 0x0010 : 0x0000);
	mask = mask | (v[5] ? 0x0020 : 0x0000);
	mask = mask | (v[6] ? 0x0040 : 0x0000);
	mask = mask | (v[7] ? 0x0080 : 0x0000);
	mask = mask | (v[8] ? 0x0100 : 0x0000);
	mask = mask | (v[9] ? 0x0200 : 0x0000);
	mask = mask | (v[10] ? 0x0400 : 0x0000);
	mask = mask | (v[11] ? 0x0800 : 0x0000);
	mask = mask | (v[12] ? 0x1000 : 0x0000);
	mask = mask | (v[13] ? 0x2000 : 0x0000);
	mask = mask | (v[14] ? 0x4000 : 0x0000);
	mask = mask | (v[15] ? 0x8000 : 0x0000);
	return mask;
}
uint16							 PrimitivBluePr::getMyBits()
{
	return boolvToMask(im);
}
uint16							 PrimitivBluePr::getColideBits()
{
	return boolvToMask(colWith);
}
float							 PrimitivBluePr::getDensity()
{
	return density;
}
float							 PrimitivBluePr::getFriction()
{
	return friction;
}
float							 PrimitivBluePr::getElasticity()
{
	return elasticity;
}
//-----------------------------------------------------------
PrimitivBluePr*					 PrimitivBluePr::draw()
{
	static float zoom = window->getView().getSize().x / WIDTH;
	//сдвиг камеры относительно центра размера окна
	sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f)*zoom + window->getView().getCenter();
	mouse = sf::Vector2f(sf::Mouse::getPosition(*window))*zoom + sdvig;//курсор с учётом сдвига
	//-------------------------------------------------------
	podsdvig = center.getPosition();//куда перетащили центор части
	//отрисовка фигур с учётом переноса центра (теперь визуально все фигуры движутся за ним в след,
	//и их Positions "есть" их положения относительно этого центра)
	//=======================================================
	//------------Рисование всех объектов части--------------
	//=======================================================
	{
		for (sf::Sprite& spr : sprite)
		{
			spr.setPosition(center.getPosition());
			window->draw(spr);
		}
		sf::Vector2f cpos = center.getPosition();
		for (SensorBpr& s : sensor) s.draw(cpos);//рисуем	все сенсоры прикреплённые к части
		drawAlg(rect.begin(), rect.end());//				все квадратные	примитивы части
		drawAlg(circle.begin(), circle.end());//			все круглые		примитивы части
		drawAlg(triang.begin(), triang.end());//			все треугольные примитивы части
	}
	//=====================================
	//--------Перемещение мышью------------
	//=====================================
	const float R = std::sqrt(
		(mouse.x - center.getPosition().x)*(mouse.x - center.getPosition().x) + 
		(mouse.y - center.getPosition().y)*(mouse.y - center.getPosition().y)
		);
	//-------------------------------------
	if (R < 20)
	{
		chosen = this;//сообщаем в статическую ссылку, что мышь выделяет именно эту часть
		sf::Vector2f pos = center.getPosition();
		characteristics.setPosition(pos.x, pos.y-window->getSize().y*0.12f);
		characteristicStringSetter(pos);
		characteristics.setStyle(0);
		if (!dontTouchThat && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !checked)
			checked = true;
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && checked)
			checked = false;

		window->draw(characteristics);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
		{
			return this;
		}
	}
	//-------------------------------------
	if (checked)
		center.setPosition(mouse);
	//-------------------------------------
	window->draw(center);
	return 0;
}
//-----------------------------------------------------------
void					PrimitivBluePr::setPosition(const sf::Vector2f& pos)
{
	center.setPosition(pos);
}
void					PrimitivBluePr::setImages(std::vector<sf::Sprite>& spr)
{
	sprite = spr;
}
void					PrimitivBluePr::addSensor(const SensorBpr& sen)
{
	sensor.push_back(sen);
}
std::vector<SensorBpr>*	PrimitivBluePr::getSensor()
{
	return &sensor;
}
//-----------------------------------------------------------
template<typename InpIterator>
void PrimitivBluePr::drawAlg(InpIterator i, InpIterator end)
{
	while (i != end)
	{
		i->move(podsdvig);
		window->draw(*i);
		i->move(-podsdvig);
		++i;
	}
}