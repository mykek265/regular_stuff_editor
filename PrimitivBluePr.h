#ifndef PRIMITIVBLUEPR_H
#define PRIMITIVBLUEPR_H
#include <vector>
#include <algorithm>
#include "SensorBpr.h"
#include "s2dpl.h"
#include "CoolFigureEditor.h"
#include "CoolFeatureWindow.h"
#include "toString.h"

class PrimitivBluePr
{
private:
	static sf::RenderWindow			*window;		//указатель на окно в котором рисовать
	static sf::Vector2f				sdvig;			//сдвиг комеры относительно центра размера окна
	static sf::Vector2f				podsdvig;
	static sf::Vector2f				mouse;			//Позиция мыши с учётом сдвига.
	static int						size;			//Кол-во частей разрабатываемой в штуке.
	//
	sf::CircleShape					center;			//Центр у каждой части "штуковины".
	std::vector<sf::RectangleShape>	rect;			//Списки квадратов,
	std::vector<sf::CircleShape>	circle;			//кругов
	std::vector<sf::ConvexShape>	triang;			//и треугольников
	std::vector<sf::Sprite>			sprite;			//и спрайтов
	std::vector<SensorBpr>			sensor;			//и сенсоров
	//Настройки
	int								type;
	float							density;
	float							friction;
	float							elasticity;
	bool							im[16];
	bool							colWith[16];
	std::string						mask;
	//
	bool							checked;		//Флаг - выбрана мышкой.
	//
	template<typename InpIterator>					//Шаблон отрисовки.
	static void drawAlg(InpIterator begin, InpIterator end);
	//отображение характеристик
	void characteristicStringSetter(const sf::Vector2f& pos);

public:
	int sn, st;
	static	bool					dontTouchThat;
	bool							loaded;			//Флаг - схема загружена(для начала работы Теста).
	static PrimitivBluePr*			chosen;			//Ссылка на выбранный объект
	static sf::Text					characteristics;
	PrimitivBluePr();
	
	PrimitivBluePr(sf::RenderWindow& window, CoolFigureEditor& cfe, CoolFeatureWindow& cfw);
	std::vector<sf::RectangleShape>& getRects();
	std::vector<sf::CircleShape>&	 getCircles();
	std::vector<sf::ConvexShape>&	 getTriangles();
	sf::Vector2f					 getCenter();
	int								 getType();
	uint16							 getMyBits();
	uint16							 getColideBits();
	float							 getDensity();
	float							 getFriction();
	float							 getElasticity();
	PrimitivBluePr* draw();
	sf::Vector2f getPosition();
	
	void setPosition(const sf::Vector2f& pos);
	void setImages(std::vector<sf::Sprite>& sprite);
	void addSensor(const SensorBpr& sensor);
	std::vector<SensorBpr>* getSensor();
	std::vector<sf::Sprite>* getImages();
	~PrimitivBluePr();
	//bool operator ==(const PrimitivBluePr& a)
	//{
	//	return this == &a;
	//}
};

#endif