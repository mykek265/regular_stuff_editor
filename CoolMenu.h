#ifndef COOLMENU_H
#define COOLMENU_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>


class CoolMenu
{
private:
	static sf::Clock clock;
	static sf::Vector2f size;
	static sf::Vector2f hideAnim;
	static sf::Vector2f sdvig;
	sf::Vector2f pos;
	static float h;
	static sf::RenderWindow* window;
	static sf::Font* font;
	int valButton;
	static std::vector<sf::RectangleShape> rect;
	std::vector<sf::Text> text;
	std::vector<sf::Vector2f> posOfB;
	static sf::Color on, off, activeOn, activeOff;
	static bool kwp;
	//побочные функции
	static void drawRect(sf::RectangleShape& rs);
	static void setZSt(sf::RectangleShape& rs);
	static void drawText(sf::Text& txt);
	static void follow(sf::RectangleShape& rs);
public:
	static int state;
	static bool active;
	CoolMenu();
	CoolMenu(sf::RenderWindow& window, sf::Font& font);
	static void setZeroState();
	void addButton(std::string& str,int size);
	void draw();
	~CoolMenu();
};

#endif