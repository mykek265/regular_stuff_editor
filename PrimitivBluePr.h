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
	static sf::RenderWindow			*window;		//��������� �� ���� � ������� ��������
	static sf::Vector2f				sdvig;			//����� ������ ������������ ������ ������� ����
	static sf::Vector2f				podsdvig;
	static sf::Vector2f				mouse;			//������� ���� � ������ ������.
	static int						size;			//���-�� ������ ��������������� � �����.
	//
	sf::CircleShape					center;			//����� � ������ ����� "���������".
	std::vector<sf::RectangleShape>	rect;			//������ ���������,
	std::vector<sf::CircleShape>	circle;			//������
	std::vector<sf::ConvexShape>	triang;			//� �������������
	std::vector<sf::Sprite>			sprite;			//� ��������
	std::vector<SensorBpr>			sensor;			//� ��������
	//���������
	int								type;
	float							density;
	float							friction;
	float							elasticity;
	bool							im[16];
	bool							colWith[16];
	std::string						mask;
	//
	bool							checked;		//���� - ������� ������.
	//
	template<typename InpIterator>					//������ ���������.
	static void drawAlg(InpIterator begin, InpIterator end);
	//����������� �������������
	void characteristicStringSetter(const sf::Vector2f& pos);

public:
	int sn, st;
	static	bool					dontTouchThat;
	bool							loaded;			//���� - ����� ���������(��� ������ ������ �����).
	static PrimitivBluePr*			chosen;			//������ �� ��������� ������
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