#ifndef SFBUTTON_H
#define SFBUTTON_H
#include <SFML\Graphics.hpp>

class sfButton
{
public:
	sf::RectangleShape shape;
	sf::Color off;
	sf::Color on;
	sf::Text text;
	bool pressed;
	sfButton();
	sfButton(sf::Color off, sf::Color on, sf::Vector2f size, sf::Vector2f pos, std::string str, sf::Font& font, int s);
	bool draw(sf::RenderWindow& window, sf::Vector2f& mouse);
	~sfButton();
};

#endif