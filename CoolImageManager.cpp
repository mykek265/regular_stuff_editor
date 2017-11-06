#include <math.h>
#include "CoolImageManager.h"
#include "windowSize.h"
#include "S2DPL\s2dplDefenitions.h"
sf::RenderWindow*			CoolImageManager::window(nullptr);
CoolScrollBar*				CoolImageManager::scrollBar(nullptr);
std::vector<sf::Texture>*	CoolImageManager::texture(nullptr);
std::vector<sf::Sprite>		CoolImageManager::sprite;
sf::Sprite					CoolImageManager::pattern;
PrimitivBluePr*				CoolImageManager::primitiv(NULL);
CoolMenu*					CoolImageManager::menu(nullptr);
sf::Vector2f				CoolImageManager::sdvig(0.f,0.f);
sf::Vector2f				CoolImageManager::mouse(0.f,0.f);
float						CoolImageManager::zoom(0.f);
int							CoolImageManager::state(0);


CoolImageManager::CoolImageManager()
{}
CoolImageManager::CoolImageManager(sf::RenderWindow& w, CoolScrollBar& csb, CoolMenu* pmenu)
{
	window = &w;
	scrollBar = &csb;
	texture = csb.getTextures();
	menu = pmenu;
	//
}


void CoolImageManager::draw()
{
	zoom = window->getView().getSize().x / WIDTH;
	sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f)*zoom + window->getView().getCenter();
	mouse = sf::Vector2f(sf::Mouse::getPosition(*window))*zoom + sdvig;

	//!--Начало изменений--!
	if (PrimitivBluePr::chosen != NULL && state == 0)
	{
		sf::Vector2f v = mouse - PrimitivBluePr::chosen->getPosition();
		float R = std::sqrt(v.x*v.x + v.y*v.y);
		if (R < 20 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			primitiv = (PrimitivBluePr::chosen);
			sprite = *primitiv->getImages();
			primitiv->getImages()->clear();
			PrimitivBluePr::dontTouchThat = true;
			state = 3;
		}
	}

	//!--Добавление изменений--!
	std::for_each(sprite.begin(), sprite.end(), [](sf::Sprite& spr){ window->draw(spr); });

	if (state >= 1)
	{
		sf::RectangleShape shape;
			shape.setOrigin(0.f, .5f);
			sf::Vector2f v = mouse -primitiv->getPosition();
			shape.setPosition(primitiv->getPosition());
			float dl = std::sqrt(v.x*v.x + v.y*v.y);
			shape.setSize({ dl, 1.f });
			shape.setRotation(std::atan2f(v.y, v.x) * s2dpl::RtoG);
		static int Nimg = 0;
		if (Nimg != scrollBar->Nimg || state == 3)
		{
			pattern.setTexture((*texture)[scrollBar->Nimg]);
			pattern.setTextureRect(sf::IntRect(0.f, 0.f, (*texture)[scrollBar->Nimg].getSize().x, (*texture)[scrollBar->Nimg].getSize().y));
			pattern.setScale(1, 1);
			pattern.setRotation(0.f);
			Nimg = scrollBar->Nimg;
		}

		{//учёт перемещения, изменений размера и угла паттерна и маркера

			pattern.setPosition(primitiv->getPosition());
			v = pattern.getOrigin();
			float d = sqrt(v.x*v.x + v.y*v.y);
			float L = 2.f * d * sin(pattern.getRotation() * 0.5f * s2dpl::GtoR);
			float angle = (90.f - pattern.getRotation()*0.5f + shape.getRotation())*s2dpl::GtoR;
			sf::Vector2f rV = { L*cos(angle), L*sin(angle) };
			pattern.setOrigin((-mouse + primitiv->getPosition()) / pattern.getScale().x + rV);
		}

		window->draw(shape);
		window->draw(pattern);

		if (state == 1 && sprite.size() && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
		{
			state = 2;
			sprite.pop_back();
		}

		if (state == 1 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			state = 2;
			sprite.push_back(pattern);
		}
		if (state >= 2 && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
			state = 1;
	}


	//!--Сохранение(отмена) изменений--!
	if (state==1 && ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::F) ))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			primitiv->setImages(sprite);
		menu->state = 0;
		menu->setZeroState();
		primitiv = (PrimitivBluePr*)NULL;
		state = 0;
		pattern = sf::Sprite();
		sprite.clear();
		PrimitivBluePr::dontTouchThat = false;
	}
}

void CoolImageManager::scrUp()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && state == 1)
		pattern.scale(1.1f, 1.1f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && state == 1)
		pattern.rotate(1.f);
}

void CoolImageManager::scrDown()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && state == 1)
		pattern.scale(0.9f, 0.9f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && state == 1)
		pattern.rotate(-1.f);
}

CoolImageManager::~CoolImageManager()
{
}
