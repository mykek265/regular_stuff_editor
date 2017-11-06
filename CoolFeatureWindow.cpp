#include "CoolFeatureWindow.h"
#include "windowSize.h"
/////////////////////////////////////////////////////////////////////
const int			CoolFeatureWindow::Nstr;
float				CoolFeatureWindow::density;
float				CoolFeatureWindow::friction;
float				CoolFeatureWindow::elasticity;
sf::RenderWindow*	CoolFeatureWindow::window;
sf::RectangleShape	CoolFeatureWindow::fon;
sf::Text			CoolFeatureWindow::str[Nstr];
sf::Vector2f		CoolFeatureWindow::sdvig(0, 0);
sf::Vector2f		CoolFeatureWindow::mouse(0, 0);
bool				CoolFeatureWindow::active;
int					CoolFeatureWindow::type(0);
std::string			CoolFeatureWindow::strType[3];
bool				CoolFeatureWindow::cwp(false);
bool				CoolFeatureWindow::im[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool				CoolFeatureWindow::icolwith[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/////////////////////////////////////////////////////////////////////
CoolFeatureWindow::CoolFeatureWindow()
{
	active = false;
}
//-------------------------------------------------------------------
CoolFeatureWindow::CoolFeatureWindow(sf::RenderWindow& w,sf::Font& f)
{
	active = false;
	window = &w;
	fon.setFillColor(sf::Color(25, 15, 25, 250));
	fon.setOutlineThickness(4);
	fon.setSize(sf::Vector2f(w.getSize().x*0.8f, w.getSize().y*0.8f));
	sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f) + window->getView().getCenter();
	mouse = sf::Vector2f(sf::Mouse::getPosition(*window)) + sdvig;//курсор с учётом сдвига

	fon.setPosition(sf::Vector2f(window->getSize().x*0.1f, window->getSize().y*0.1f) + sdvig);
	for (int i = 0; i < Nstr; i++)
	{
		str[i].setFont(f);
		str[i].setColor(sf::Color(105, 115, 255, 255));
		str[i].setCharacterSize(14);
	}
	{// init строк
		strType[0] = "Static";
		strType[1] = "Dynamic";
		strType[2] = "Kinematic";
		str[0].setString('<');
		str[1].setString('>');
		str[2].setString("Ok");
		str[3].setString("Cancel");
		str[4].setString("^\nv");
		str[5] = str[4];
		str[10]= str[4];
		str[6].setString("Type \t\t" + strType[type]);
		str[7].setString("Densyty");
		str[8].setString("Set Default");
		str[9].setString("Fricuency");
		str[11].setString("Elasticity");
		str[12].setString("I'm a:");
		str[13].setString("I colide\nwith:");
		for (int i = 14; i < Nstr; i++)
			str[i].setString("[ ]");
	}
}
//-------------------------------------------------------------------
short CoolFeatureWindow::draw()
{
	str[6].setString("Type \t\t" + strType[type]);
	str[7].setString("Density: " + toString(density));
	str[9].setString("Fricuency: " + toString(friction));
	str[11].setString("Elasticity: " + toString(elasticity));
	static float zoom = window->getView().getSize().x / WIDTH;
	sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f)*zoom + window->getView().getCenter();
	mouse = sf::Vector2f(sf::Mouse::getPosition(*window))*zoom + sdvig;//курсор с учётом сдвига
	//Разметка
	fon.setPosition(sf::Vector2f(window->getSize().x*0.1f, window->getSize().y*0.1f) + sdvig);
	window->draw(fon);
	str[0].setPosition(sdvig.x + window->getSize().x*0.24f, sdvig.y + window->getSize().y*0.24f);//	 < - стрелочка типа влево
	str[1].setPosition(sdvig.x + window->getSize().x*0.3f, sdvig.y + window->getSize().y*0.24f); //	 > - стрелочка типа вправо
	str[2].setPosition(sdvig.x + window->getSize().x*0.3f, sdvig.y + window->getSize().y*0.75f);//	 кнопка "Ok"
	str[3].setPosition(sdvig.x + window->getSize().x*0.7f, sdvig.y + window->getSize().y*0.75f);//	 кнопка "Отмена"
	str[4].setPosition(sdvig.x + window->getSize().x*0.2f, sdvig.y + window->getSize().y*0.32f);//   ^v - ползунок для density
	str[5].setPosition(sdvig.x + window->getSize().x*0.4f, sdvig.y + window->getSize().y*0.32f);//   ^v - ползунок для fricuency
	str[10].setPosition(sdvig.x + window->getSize().x*0.25f, sdvig.y + window->getSize().y*0.42f);// ^v - ползунок для elasticity!
	str[6].setPosition(sdvig.x + window->getSize().x*0.2f, sdvig.y + window->getSize().y*0.24f);//	 Type  настоящий тип
	str[7].setPosition(sdvig.x + window->getSize().x*0.2f, sdvig.y + window->getSize().y*0.28f);//	 Density:   значение 
	str[9].setPosition(sdvig.x + window->getSize().x*0.4f, sdvig.y + window->getSize().y*0.28f);//   Friction:  значение
	str[11].setPosition(sdvig.x + window->getSize().x*0.25f, sdvig.y + window->getSize().y*0.38f);// Elasticity:значение
	str[8].setPosition(sdvig.x + window->getSize().x*0.21f, sdvig.y + window->getSize().y*0.79f);//	 Кнопка SetDefault
	str[12].setPosition(sdvig.x + window->getSize().x*0.45f, sdvig.y + window->getSize().y*0.50f);//  Строка - "Я есть:"
	str[13].setPosition(sdvig.x + window->getSize().x*0.45f, sdvig.y + window->getSize().y*0.60f);// Строка - "Я хочу сталкиваться с:"
	for (int i = 14; i < 30; i++)
		str[i].setPosition(sdvig.x + window->getSize().x*0.48f + 20.f * (i-14), sdvig.y + window->getSize().y * 0.53f);//чекбоксы
	for (int i = 30; i < Nstr; i++)
		str[i].setPosition(sdvig.x + window->getSize().x*0.48f + 20.f * (i-30), sdvig.y + window->getSize().y * 0.63f);//чекбоксы
	//Логика
	for (int i = 0; i < Nstr; i++)
	{
		if (i!=4 && i!=5 && i!=10) str[i].setStyle(0);
		sf::Vector2f pos = str[i].getPosition();
		//отзывчивость однострочных элементов
		if (mouse.x>pos.x&&mouse.y > pos.y&&mouse.x < pos.x + str[i].getString().getSize() * 6 && mouse.y < pos.y + 14 &&
			i != 4  && i != 5  && i!=10  &&			//т.е. не ползунки
			i != 12 && i != 13 &&					//, не заголовки таблицы масок
			i != 6  && i != 7  && i != 9 && i != 11)//и не строки
			str[i].setStyle(3);
		//отзывчивость двухстрочных элементов
		if (mouse.x>pos.x&&mouse.y > pos.y&&mouse.x < pos.x + str[i].getString().getSize() * 10 && mouse.y < pos.y + 14 * 3 &&
			i != 6 && i != 7 && i != 9 && i < 11)//т.е. не строки и не элементы таблицы масок
			str[i].setStyle(3);
		window->draw(str[i]);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !cwp)
	{
		//по нажатию < и > для настройки типа
		if (str[0].getStyle() == 3)	type--;
		if (str[1].getStyle() == 3)	type++;
		if (type == -1)	type = 2;
		if (type == 3)	type = 0;
		//по нажатию set def
		if (str[8].getStyle() == 3) 
		{
			if (type == 0)
			{
				density = 0.f;
				friction = 0.35f;
				elasticity = 0.05f;
				for (int i = 0; i < 16; i++)
				{
					im[i] = false;
					str[i + 14].setString("[ ]");
					icolwith[i] = true;
					str[i + 30].setString("[+]");
				}
			}
			if (type == 1)
			{
				density = 1.f;
				friction = 0.35f;
				elasticity = 0.05f;
				for (int i = 0; i < 16; i++)
				{
					im[i] = false;
					str[i + 14].setString("[ ]");
					icolwith[i] = true;
					str[i + 30].setString("[+]");
				}
			}
			if (type == 2)
			{
				density = 1.f;
				friction = 0.35f;
				elasticity = 0.05f;
				for (int i = 0; i < 16; i++)
				{
					im[i] = false;
					str[i + 14].setString("[ ]");
					icolwith[i] = false;
					str[i + 30].setString("[ ]");
				}
			}
		}
		//по нажатию на чекбокс
		for (int i = 14; i < 30; i++)
			if (str[i].getStyle() == 3)
				str[i].setString(((im[i - 14] = !im[i - 14]) ? "[+]" : "[ ]"));
		for (int i = 30; i < Nstr; i++)
			if (str[i].getStyle() == 3)
				str[i].setString(((icolwith[i - 30] = !icolwith[i - 30]) ? "[+]" : "[ ]"));
		cwp = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bool tr[3] = { str[4].getStyle() == 3, str[5].getStyle() == 3, str[10].getStyle() == 3 };
		//по нажатию на ползунок density
		if (tr[0]) density = int((-fon.getPosition().y + mouse.y)*.05f * 1000)*.001f;
		//по нажатию на ползунок friction
		if (tr[1]) friction = int((-fon.getPosition().y + mouse.y)*.05f * 1000)*.001f;
		//по нажатию на ползунок elasticity!
		if (tr[2]) elasticity = int((-fon.getPosition().y + mouse.y)*.05f * 1000)*.001f;
		if (!(tr[0]||tr[1]||tr[2]))
		{
			//по нажатию на Ok
			if (str[2].getStyle() == 3) return 1;
			//по нажатию на Отмена
			if (str[3].getStyle() == 3) return 2;
		}
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{	//фиксация ползунков
		str[4].setStyle(0);
		str[5].setStyle(0);
		str[10].setStyle(0);
		cwp = false;
	}
	return 0;
}
//-------------------------------------------------------------------
CoolFeatureWindow::~CoolFeatureWindow()
{
}
