#ifndef COOLSCROLLBAR_H
#define COOLSCROLLBAR_H
#include <SFML\Graphics.hpp>
#include <fstream>
#include <vector>
#include <string> 
#include <sstream>
#include "toString.h"

class CoolScrollBar//для выбора картинок или спрайтовых анимаций
{
private:
	static sf::RenderWindow*		window;
	static sf::RectangleShape		rect[2];
	static sf::CircleShape			circle;
	static sf::Vector2f				sdvig;
	static sf::Color				defRectColor;
	static std::vector<sf::Texture>	texture;
	static std::vector<sf::Sprite>	img;
public:
	int								Nimg;
	static int						state;
	CoolScrollBar();
	CoolScrollBar(sf::RenderWindow& winow);
	~CoolScrollBar();
	void scrUp();
	void scrDown();
	void draw();
	static std::vector<sf::Texture>* getTexturesStatic();
	std::vector<sf::Texture>* getTextures();
};


#endif