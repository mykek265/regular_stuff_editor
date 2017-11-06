#ifndef SENSOR_H
#define SENSOR_H
#include "s2dplDefenitions.h"
#include <vector>

namespace s2dpl
{
	class Sensor
	{
	public:
	//��������� ����� �� ������� ����� ����� ����� ������ ����
		std::string id;
		static std::map<std::string, Sensor*> sensor;//��� �������, ������� �����-���� ������������ 
		static std::vector<std::string> deleted;
		int No;//���������� ����� � ���� �������
		b2Body* physics;
	protected:
		sf::Vector2f pos;
		float angle;
		sf::RectangleShape			rectangle;
		int							contact;
		static	b2World*			world;
		static	sf::RenderWindow*	window;
	public:
		Sensor();
		~Sensor();
		void startContact();
		void endContact();
		int speak();//�������, ��� ������
		void draw();//����������, ��� ���������
		//����� ��������� ����� �� ���� ���
		static void init(b2World& world, sf::RenderWindow& window);
	};
}

#endif