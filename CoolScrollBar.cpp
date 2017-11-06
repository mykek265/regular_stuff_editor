#include "CoolScrollBar.h"

sf::RenderWindow*		CoolScrollBar::window;
sf::RectangleShape		CoolScrollBar::rect[2];
sf::CircleShape			CoolScrollBar::circle;
sf::Vector2f			CoolScrollBar::sdvig(0, 0);
sf::Color				CoolScrollBar::defRectColor(200, 200, 200, 220);
int						CoolScrollBar::state(0);
std::vector<sf::Texture>CoolScrollBar::texture;
std::vector<sf::Sprite>	CoolScrollBar::img;

CoolScrollBar::CoolScrollBar()
	:Nimg(0)
{
}
CoolScrollBar::CoolScrollBar(sf::RenderWindow& w)
	:Nimg(0)
{
	window = &w;

	//Загрузка всех текстурок из папки img
	sf::Texture t;
	int i = 0;
	while (t.loadFromFile("img/" + toString(i) + ".png"))
	{
		texture.push_back(t);
		i++;
	}

	//инициализация внешнего вида ScrollBar-а
	for (int i = 0; i < 2; i++)
	{
		rect[i].setSize(sf::Vector2f(60, 60));
		rect[i].setOrigin(rect[0].getSize().x*0.5f, rect[0].getSize().y*0.5f);
		rect[i].rotate(45);
		rect[i].setPosition(1290, 680 - i * 110);
		rect[i].setFillColor(defRectColor);
	}
	circle.setRadius(35.f);
	circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
	circle.setFillColor(sf::Color(200, 200, 200, 220));
	circle.setPosition(1290, 630);
	circle.setOutlineThickness(2);
	circle.setOutlineColor(sf::Color(0, 122, 204, 255));

	//загрузка текстурок в спрайты
	std::for_each(texture.begin(), texture.end(), [](const sf::Texture& tex)
	{
		std::auto_ptr<sf::Sprite> spr(new sf::Sprite);//просто попробовал автоматический указатель
		spr->setTexture(tex);
		img.push_back(*spr);
	});

	//изменение размера спрайтов для скроллБара
	sf::Vector2f size;
	for (int i = 0; i < texture.size(); i++)
	{
		size = sf::Vector2f(texture[i].getSize());
		float sc = 100.f / (size.x > size.y ? size.x : size.y);
		img[i].setScale(sc, sc);
		img[i].setPosition(circle.getPosition());
		img[i].setOrigin(size*.5f);
	}
}

void CoolScrollBar::draw()
{


	
	//отрисовка скроллБара
	sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f) + window->getView().getCenter();
	static int cyScr(0);
	for (int i = 0; i < 2; i++)
	{
		rect[i].move(sdvig);
		if (rect[i].getFillColor() != defRectColor)
		{
			cyScr++;
			if (cyScr >= 3)
			{
				cyScr = 0;
				rect[i].setFillColor(defRectColor);
			}
		}
		window->draw(rect[i]);
		rect[i].move(-sdvig);
	}
	circle.move(sdvig);
	img[Nimg].move(sdvig);
		window->draw(circle);
		window->draw(img[Nimg]);
	img[Nimg].move(-sdvig);
	circle.move(-sdvig);
}
void CoolScrollBar::scrUp()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		rect[0].setFillColor(sf::Color::Red);
		Nimg--;
		if (Nimg < 0) Nimg = img.size()-1;
	}
}
void CoolScrollBar::scrDown()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		rect[1].setFillColor(sf::Color::Red);
		Nimg++;
		if (Nimg >= img.size()) Nimg = 0;
	}
}

std::vector<sf::Texture>* CoolScrollBar::getTexturesStatic()
{
	return &texture;
}
std::vector<sf::Texture>* CoolScrollBar::getTextures()
{
	return &texture;
}

CoolScrollBar::~CoolScrollBar()
{
}
