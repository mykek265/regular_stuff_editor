#ifndef JOINTBLUEPR_H
#define JOINTBLUEPR_G
#include "s2dpl.h"
#include "PrimitivBluePr.h"
#include <iostream>


class JointBluePr
{
private:
	static int				click;		//цикл кликов
	static bool				kwp;		//key was pressed
	static float			zoom;
	static sf::Vector2f		sdvig;
	static sf::Vector2f		mouse;
	sf::RectangleShape		line[2];	//плечи
	sf::RectangleShape		joint;		//точки соединения
	sf::RectangleShape		minLim;		//лимиты
	sf::RectangleShape		maxLim;
	float					distance;	//растояние от мыши до соединения
	void					characteristicStringSetter();
	void updateLines();
public:
	static sf::Text			characteristics;
	static sf::RenderWindow	*window;
	bool					checked;	//флаг - соединение выбрано мышью(щелчёк состоялся)
	bool					mustToBeErased;
	PrimitivBluePr			*primitivA;
	PrimitivBluePr			*primitivB;
	bool					enableLimit;
	float						maxl, minl;
	bool					enableMotor;
	float						speed, force;
	//bool					enableMuscul;
	float						angle;
	float					normal;
	/*-Anable types:-*/
	/*0=freeRevalue  |1=Revalue   with Motor|2=ServoRev |
	  3=freePrismatic|4=Prismatic with Motor|5=ServoPrsm|*/
	int						type;
	JointBluePr();
	JointBluePr(PrimitivBluePr* A, PrimitivBluePr* B, sf::Vector2f center);
	sf::Vector2f getPosition();
	void draw();
	void drWithoutUpdates(const sf::Vector2f& pos);
	float getAAngle();
	~JointBluePr();
};

#endif