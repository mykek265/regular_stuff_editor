#include "JointBluePr.h"
#include "windowSize.h"
#include <algorithm>

int					JointBluePr::click;		//цикл кликов
bool				JointBluePr::kwp;		//key was pressed
float				JointBluePr::zoom;
sf::Vector2f		JointBluePr::sdvig;		//сдвиг камеры от view по умолчанию
sf::Vector2f		JointBluePr::mouse;		//положение мыши
sf::Text			JointBluePr::characteristics;
sf::RenderWindow*	JointBluePr::window;



void JointBluePr::characteristicStringSetter()
{
	characteristics.setPosition(joint.getPosition().x, joint.getPosition().y - window->getSize().y*0.12f);
	characteristics.setString(
		"Position:(" + toString(joint.getPosition().x) + ", " + toString(joint.getPosition().y) + ")\n" +
		"type: " + (type<3 ? (type == 0 ? "freeRevalue" : type == 1 ? "Revalue with Motor" : "ServoRev") : (type == 3 ? "freePrismatic" : type == 4 ? "Prismatic with Motor" : "ServoPrsm")) +
		(enableLimit ? (",\nLimit from " + toString(minl) + " to " + toString(maxl)) : "") +
		(enableMotor ? (", Motor with speed(" + toString(speed) + ") and force(" + toString(force) + ')') : "")
		);
}

JointBluePr::JointBluePr()
	:checked(false),
	mustToBeErased(false),
	primitivA(NULL),
	primitivB(NULL),
	enableLimit(false),
	maxl(0.f), minl(0.f),
	enableMotor(false),
	speed(0.f), force(0.f),
	angle(0.f),
	normal(0.f),
	type(0)
{
}


JointBluePr::JointBluePr(PrimitivBluePr* pA, PrimitivBluePr* pB, sf::Vector2f pos)
	:checked(false),
	mustToBeErased(false),
	primitivA(pA),
	primitivB(pB),
	enableLimit(false),
	maxl(0.f), minl(0.f),
	enableMotor(false),
	speed(0.f), force(0.f),
	angle(0.f),
	normal(0.f),
	type(0)									
{
	joint.setFillColor(sf::Color(100, 180, 200, 255));
	joint.setSize({ 8.f, 8.f });
	joint.setOrigin(4.f, 4.f);
	joint.setRotation(45);
	joint.setOutlineThickness(1);
	joint.setOutlineColor(sf::Color::Yellow);
	joint.setPosition(pos);
	
	for (int i = 0; i < 2; i++)
	{
		const sf::Vector2f v = (i == 0 ? primitivA : primitivB)->getPosition() - pos;
		float l = sqrt(v.x*v.x + v.y*v.y);
		line[i].setFillColor(sf::Color(100, 180, 200, 255));
		line[i].setOrigin(0, .5f);
		line[i].setPosition(pos);
		line[i].setSize({ l, 1 });
		line[i].setRotation(std::atan2f(v.x, -v.y) * 57.2958f-90.f);
	}
}
void JointBluePr::draw()
{
	zoom = window->getView().getSize().x / WIDTH;
	sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f)*zoom + window->getView().getCenter();
	mouse = sf::Vector2f(sf::Mouse::getPosition(*window))*zoom + sdvig;//положение мыши с учётом сдвига и zoomа
	
	sf::Vector2f jpos = joint.getPosition()-mouse;
	distance = std::sqrtf(jpos.x*jpos.x + jpos.y*jpos.y);
	if (distance < 30 && primitivA && primitivB)//noted
	{
		characteristicStringSetter();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !checked)
			checked = true;
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && checked)
			checked = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
			mustToBeErased = true;
		window->draw(characteristics);

	}
	if (checked)	joint.setPosition(mouse);

	updateLines();



	window->draw(line[0]);
	window->draw(line[1]);
	window->draw(joint);
}
void JointBluePr::drWithoutUpdates(const sf::Vector2f& pos)
{
	angle = line[1].getRotation() - line[0].getRotation();
	sf::Vector2f buf=line[0].getPosition();
	line[0].setPosition(pos);
	window->draw(line[0]);
	line[0].setPosition(buf);
	buf = line[1].getPosition();
	line[1].setFillColor(sf::Color::Magenta);
	line[1].setPosition(pos);
	window->draw(line[1]);
	line[1].setFillColor(line[0].getFillColor());
	line[1].setPosition(buf);
	buf = joint.getPosition();
	joint.setPosition(pos);
	window->draw(joint);
	joint.setPosition(buf);
}
float JointBluePr::getAAngle()
{
	return line[0].getRotation();
}
sf::Vector2f JointBluePr::getPosition()
{
	return joint.getPosition();
}



JointBluePr::~JointBluePr()
{
}
inline void JointBluePr::updateLines()
{
	for (int i = 0; i < 2; i++)
	{
		const sf::Vector2f v = (i == 0 ? primitivA : primitivB)->getPosition() - joint.getPosition();
		const float l = sqrt(v.x*v.x + v.y*v.y);
		line[i].setPosition(joint.getPosition());
		line[i].setSize({ l, 1 });
		line[i].setRotation(std::atan2f(v.x, -v.y) * 57.2958f-90.f);
	}
	angle = line[1].getRotation() - line[0].getRotation();
}