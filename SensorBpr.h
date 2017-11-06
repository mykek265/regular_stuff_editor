#ifndef SENSORBPR_H
#define SENSORBPR_H
#include <SFML/Graphics.hpp>
class SensorBpr
{
private:
	sf::RectangleShape shape;//������������� ��������� �����
	sf::RectangleShape line;//������������� ����
	sf::CircleShape center;//������������� �����, �� ������� �� ����� ������ ������������� �� ������� � �������
	static sf::Vector2f vec;
public:
	static sf::RenderWindow* window;//�������������, ��� �� ��� �� ���
	SensorBpr();//�.�. �� ��� �� UE4 ��������
	SensorBpr(const sf::Vector2f& size, const sf::Vector2f& pos/*, PrimitivBluePr* prim*/);
	~SensorBpr();
	void draw(const sf::Vector2f& pos);
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
};

#endif