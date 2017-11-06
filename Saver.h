#ifndef SAVER_H
#define SAVER_H
#include <fstream>
#include <iostream>
#include "s2dpl.h"
#include "toString.h"
#include "CoolMenu.h"
#include "windowSize.h"
//#include "JointBluePr.h"
#include "CoolJointManager.h"
//#include "PrimitivBluePr.h"
#include "CoolFigureEditor.h"

class Saver
{
private:
	static std::string					_name;
	static sf::RenderWindow*			_window;
	static sf::View*					_view;
	static sf::Vector2f*				_mouse;
	static sf::RectangleShape			_fon;
	static sf::Text						_tx_name;
	static sf::Text						_str;
	static std::vector<PrimitivBluePr>*	_blpr;
	static std::vector<JointBluePr>*	_jblpr;
private:
	bool isButtonChoosen(const sf::Vector2f& b, const sf::Vector2f& mouse)
	{
		return (mouse.x > b.x && mouse.x < b.x + 70.f && mouse.y > b.y && mouse.y < b.y + 20.f);
	}
	void setLiteButton(const std::string& str0, const sf::Vector2f& center, const sf::Vector2f& fonOrg, const float& x, const float& y, const sf::Vector2f& mouse, int& question, const int& q)
	{
		_str.setPosition(sf::Vector2f(x*fonOrg.x, y*fonOrg.y) + center);
		_str.setString(str0);
		_str.setStyle(0);
		if (isButtonChoosen(_str.getPosition(), mouse))
		{
			_str.setStyle(1);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				question = q;
			}
		}
	}
	void setLiteString(const std::string& str0, const sf::Vector2f& center, const sf::Vector2f& fonOrg, const float& x, const float& y, sf::Text& str)
	{
		str.setPosition(sf::Vector2f(x*fonOrg.x, y*fonOrg.y) + center);
		str.setString(str0);
		str.setStyle(0);
	}
	void saveBlPr(std::ofstream& fout, PrimitivBluePr& blpr);
	void saveBlPr_plus(std::ofstream& fout, PrimitivBluePr& blpr);
public:
	static int _state;
	Saver();
	Saver(sf::RenderWindow& window, sf::View& view, sf::Vector2f& mouse, sf::Text& str, std::vector<PrimitivBluePr>& blpr, CoolJointManager& coolJm);
	void draw();
	void enterName(const std::string& str);
	void save();
	void save_plus();
	~Saver();
};

#endif