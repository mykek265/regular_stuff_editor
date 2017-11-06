#include "sfButton.h"


sfButton::sfButton() :pressed(false)
{
}

sfButton::sfButton(sf::Color soff, sf::Color son,sf::Vector2f size,sf::Vector2f pos, std::string sstr, sf::Font& font, int s)
	: off(soff), on(son), pressed(false)
{
	shape.setFillColor(soff);
	shape.setSize(size);
	shape.setPosition(pos);
	text.setFont(font);
	text.setPosition(pos.x+2,pos.y-2);
	text.setString(sstr);
	text.setCharacterSize(s);
}

bool sfButton::draw(sf::RenderWindow& window, sf::Vector2f& mouse)
{
	sf::Vector2f sdvig = -sf::Vector2f(window.getSize().x*0.5f, window.getSize().y*0.5f) + window.getView().getCenter();
	shape.move(sdvig);
	text.move(sdvig);
	bool x=false;
	sf::Vector2f pos(shape.getPosition()), size(shape.getSize()+pos);
	if ((mouse.x<size.x && mouse.x>pos.x) && (mouse.y<size.y && mouse.y>pos.y))
	{
		pressed = true;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) x = true;
	}
	else pressed = false;
	if(!(sf::Mouse::isButtonPressed(sf::Mouse::Left))) x = false;
	pressed ? shape.setFillColor(on) : shape.setFillColor(off);
	window.draw(this->shape);
	window.draw(this->text);
	shape.move(-sdvig);
	text.move(-sdvig);
	return x;
}

sfButton::~sfButton()
{
}
