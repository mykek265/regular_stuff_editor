#include "CoolMenu.h"
#include "windowSize.h"

sf::Color			CoolMenu::on(109, 89, 242, 255);
sf::Color			CoolMenu::activeOn(146, 134, 239, 255);
sf::Color			CoolMenu::off(57, 58, 63, 255);
sf::Color			CoolMenu::activeOff(83, 84, 91, 255);
sf::Clock			CoolMenu::clock;
sf::RenderWindow*	CoolMenu::window;
sf::Font*			CoolMenu::font;
sf::Vector2f		CoolMenu::size;
sf::Vector2f		CoolMenu::hideAnim(0,0);
sf::Vector2f		CoolMenu::sdvig(0,0);
float				CoolMenu::h(0.f);
bool				CoolMenu::kwp(false);
int					CoolMenu::state(0);
std::vector<sf::RectangleShape> CoolMenu::rect;
static float zoom(0);

CoolMenu::CoolMenu()
{
	state = 0;
}

CoolMenu::CoolMenu(sf::RenderWindow& w, sf::Font& f)
{
	state = 0;
	window = &w;
	size=sf::Vector2f(w.getSize().x*0.2f, h=w.getSize().y*0.05f);
	pos.x = 0;
	pos.y = (w.getSize().y-h)*0.5;
	font = &f;

}
void CoolMenu::addButton(std::string& str, int sz)
{
	sf::RectangleShape rs;
	rs.setFillColor(off);
	rs.setSize(size);
	for (int i = 0; i < rect.size(); i++)
	{
		rect[i].move(0, -h*0.5f);
		text[i].move(0, -h*0.5f);
		rect[i].move(-float(window->getSize().x*0.5f), -float(window->getSize().y*0.5f));
		rect[i].move(window->getView().getCenter());
		text[i].move(-float(window->getSize().x*0.5f), -float(window->getSize().y*0.5f));
		text[i].move(window->getView().getCenter());
	}
	rs.setPosition(pos.x, pos.y + h*0.5f*valButton);
	rs.setOutlineThickness(1);
	rs.setOutlineColor(sf::Color(0, 122, 204, 255));
	valButton++;
	//
	sf::Text txt;
	txt.setColor(sf::Color::White);
	txt.setFont(*font);
	txt.setPosition(15+pos.x, pos.y + h*0.5f*valButton-8);
	txt.setCharacterSize(sz);
	txt.setColor(sf::Color::White);
	txt.setString(str);
	//
	rect.push_back(rs);
	text.push_back(txt);
}
void CoolMenu::draw()
{

	zoom = window->getView().getSize().x / WIDTH;
	std::for_each(rect.begin(), rect.end(), CoolMenu::drawRect);
	std::for_each(text.begin(), text.end(), CoolMenu::drawText);
	pos += -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f) + window->getView().getCenter();
	for (int i = 0; i < rect.size(); i++)
		if (rect[i].getFillColor() == activeOn || rect[i].getFillColor() == on)
		{
			state = i+1;
			break;
		}
	if (clock.getElapsedTime()>sf::seconds(4))
		clock.restart();
}

CoolMenu::~CoolMenu()
{
}
void CoolMenu::drawRect(sf::RectangleShape& rs)
{
	if (clock.getElapsedTime()>sf::seconds(1)&&hideAnim.x>-size.x*0.98)
		hideAnim.x -= 0.2;
	//
	sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f) + window->getView().getCenter() + hideAnim;
	rs.move(sdvig);
	//
	sf::Color con = rs.getFillColor();
	//
	if (con == activeOff)	con = off;
	if (con == activeOn)	con = on;
	sf::Vector2f mous(sf::Mouse::getPosition(*window)), p = (rs.getPosition());
	mous -= sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f);
	mous *= zoom;
	mous += window->getView().getCenter();
	if (p.x<mous.x&&p.y<mous.y&&p.x + size.x>mous.x&&p.y + size.y>mous.y)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!kwp)
		{
			if (!(state&&con==on))
			{
				con = on;
				rs.move(10, 0);
			}
			if (state&&con==on)
			{
				con = off;
				rs.move(-10, 0);
				state = 0;
			}
			kwp = true;
		}
		clock.restart();
		if(hideAnim.x<0)
			hideAnim.x += 10;
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) kwp = false;
		con = con == off ? activeOff : activeOn;
	}
	rs.setFillColor(con);
	//
	window->draw(rs);
	rs.move(-sdvig);
}
void CoolMenu::drawText(sf::Text& txt)
{
	sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f) + window->getView().getCenter() + hideAnim;
	txt.move(sdvig);
	window->draw(txt);
	txt.move(-sdvig);
}
void CoolMenu::setZSt(sf::RectangleShape& rs)
{
	sf::Color con = rs.getFillColor();
	if (con == on) rs.setFillColor(off);
	if (con == activeOn) rs.setFillColor(activeOff);
	if (con == on || con == activeOn)
		rs.move(-10,0);
	state = 0;
}
void CoolMenu::setZeroState()
{
	std::for_each(rect.begin(), rect.end(), CoolMenu::setZSt);
}