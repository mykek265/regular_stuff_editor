#ifndef SENSORBPR_H
#define SENSORBPR_H
#include <SFML/Graphics.hpp>
class SensorBpr
{
private:
	sf::RectangleShape shape;//символизирует окончание нерва
	sf::RectangleShape line;//символизирует нерв
	sf::CircleShape center;//символизирует ебалу, за которую мы можем сенсор перетаскивать из стороны в сторону
	static sf::Vector2f vec;
public:
	static sf::RenderWindow* window;//символизирует, что всё идёт на хуй
	SensorBpr();//т.к. мы тут не UE4 собираем
	SensorBpr(const sf::Vector2f& size, const sf::Vector2f& pos/*, PrimitivBluePr* prim*/);
	~SensorBpr();
	void draw(const sf::Vector2f& pos);
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
};

#endif