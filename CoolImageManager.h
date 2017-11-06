#ifndef COOLIMAGEMANAGER_H
#define COOLIMAGEMANAGER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "CoolScrollBar.h"
#include "CoolMenu.h"
#include "PrimitivBluePr.h"

class CoolImageManager
{
private:
	static sf::RenderWindow*			window;
	static CoolScrollBar*				scrollBar;
	static std::vector<sf::Texture>*	texture;
	static std::vector<sf::Sprite>		sprite;		//которые можем видоизменять и чъи position уже закреплены(мы меняем только scale, origen и возможно угол)
	static sf::Sprite					pattern;	//который лепим
	static PrimitivBluePr*				primitiv;	//с которым мы работаем в сеанс
	static CoolMenu*					menu;
	static sf::Vector2f					sdvig;
	static sf::Vector2f					mouse;
	static float						zoom;
	static int							state;
public:
	CoolImageManager();
	CoolImageManager(sf::RenderWindow& window, CoolScrollBar& scrollBar, CoolMenu* menu);
	~CoolImageManager();
	void draw();
	void scrUp();
	void scrDown();
};

#endif