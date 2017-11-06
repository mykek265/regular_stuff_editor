#include "CoolFigureEditor.h"
#include "windowSize.h"
#include <iostream>
sf::RenderWindow*	CoolFigureEditor::window;
int					CoolFigureEditor::state(0);
int					CoolFigureEditor::lastPolNo(0);
int					CoolFigureEditor::clkm2(0);
sf::Vector2f		CoolFigureEditor::pointForS[3];
sf::RectangleShape	CoolFigureEditor::rectM;
sf::CircleShape		CoolFigureEditor::circleM;
sf::ConvexShape		CoolFigureEditor::triangM;
sf::Vector2f		CoolFigureEditor::sdvig(0, 0);
sf::Time			CoolFigureEditor::KWPline(sf::seconds(0.19f));
bool				CoolFigureEditor::rectTrig(false);
bool				CoolFigureEditor::circleTrig(false);
bool				CoolFigureEditor::newConv(true);
sf::Clock			CoolFigureEditor::KWP;
sf::RectangleShape*	CoolFigureEditor::rectBrush = NULL;
sf::CircleShape*	CoolFigureEditor::circleBrush = NULL;
sf::ConvexShape*	CoolFigureEditor::convBrush = NULL;
sf::CircleShape		CoolFigureEditor::center;

static float		zoom(1);

CoolFigureEditor::CoolFigureEditor()
{
}

CoolFigureEditor::CoolFigureEditor(sf::RenderWindow& w)
{
	window = &w;
	//
	rectM.setFillColor(sf::Color(255, 255, 255, 100));
	const sf::Vector2f const sizeM = sf::Vector2f(window->getSize());
	const float const sizeM_y = 0.06510416667*sizeM.y;
	rectM.setSize(sf::Vector2f(sizeM_y, sizeM_y));
	rectM.setOrigin(rectM.getSize().x*0.5f, rectM.getSize().y*0.5f);
	rectM.setPosition(sizeM.x*0.84187408492f, sizeM.y*0.88541666667f);
	//
	circleM.setFillColor(sf::Color(255, 255, 255, 100));
	circleM.setRadius(sizeM_y / 2);
	circleM.setOrigin(circleM.getRadius(), circleM.getRadius());
	circleM.setPosition(sizeM.x*0.88067349927f, sizeM.y*0.88541666667f);
	//
	triangM.setFillColor(sf::Color(255, 255, 255, 100));
	triangM.setPointCount(3);
	sf::Vector2f v[3] = { { (-sizeM_y / 2), (-sizeM_y / 2) }, { (sizeM_y / 1.2f), (-sizeM_y / 3) }, { (-sizeM_y / 10.f), sizeM_y / 1.2f } };
	triangM.setPoint(0, v[0]);
	triangM.setPoint(1, v[1]);
	triangM.setPoint(2, v[2]);
	triangM.setPosition(sizeM.x*0.91361639824f, sizeM.y*0.87890625f);
	//
	state = 0;
	updateMenuColor();
	//
	center.setFillColor(sf::Color(0, 148, 255, 150));
	center.setPosition(sf::Vector2f(window->getView().getCenter()));
	center.setRadius(10);
	center.setOrigin(10,10);
	//
}
void CoolFigureEditor::Mod3()
{//Идущий на смерть, приветствую тебя)
	int polNo = triangle.size();
	sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*window))*zoom+sdvig;
	switch (state)
	{
	case 0://Прямоугоша MOD
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) && (KWP.getElapsedTime() > KWPline) && !rectTrig && rect.size())
		{
			rect.pop_back();
			KWP.restart();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (KWP.getElapsedTime() > KWPline) && !rectTrig)
		{
			rectBrush = new sf::RectangleShape();
			rectBrush->setFillColor(sf::Color(0, 255, 123, 100));
			rectBrush->setOutlineThickness(1);
			KWP.restart();
			rectBrush->setPosition(mouse.x, mouse.y);
			rectTrig = true;
		}
		if (rectTrig)
		{
			rectBrush->setSize(sf::Vector2f((mouse.x - rectBrush->getPosition().x), (mouse.y - rectBrush->getPosition().y)));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rectTrig && (KWP.getElapsedTime() > KWPline))
			{
				KWP.restart();
				rect.push_back(*rectBrush);
				delete rectBrush;
				rectBrush = NULL;
				rectTrig = false;
			}
		}
		break;
	////////////////////////////////////////////////////////////////////////////////////////////
	case 1://Кругляш MOD
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) && (KWP.getElapsedTime() > KWPline) && !circleTrig && circle.size())
		{
			circle.pop_back();
			KWP.restart();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (KWP.getElapsedTime() > KWPline) && !circleTrig){
			circleBrush = new sf::CircleShape();
			circleBrush->setFillColor(sf::Color(255, 106, 0, 100));
			circleBrush->setOutlineThickness(1);
			KWP.restart();
			circleBrush->setPosition(mouse.x, mouse.y);
			circleTrig = true;
		}
		if (circleTrig){
			circleBrush->setRadius(sqrt(pow(mouse.x - circleBrush->getPosition().x, 2) + pow(mouse.y - circleBrush->getPosition().y, 2)));
			circleBrush->setOrigin(circleBrush->getRadius(), circleBrush->getRadius());
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && circleTrig && (KWP.getElapsedTime() > KWPline)){
				KWP.restart();
				circle.push_back(*circleBrush);
				delete circleBrush;
				circleBrush = NULL;
				circleTrig = false;
			}
		}
		break;
	////////////////////////////////////////////////////////////////////////////////////////////
	case 2://Полигоша MOD
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) && (KWP.getElapsedTime() > KWPline) && !clkm2 && triangle.size())
		{
			triangle.pop_back();
			if (triangle.size())
				triangle[triangle.size() - 1].setOutlineThickness(0.5f);
			KWP.restart();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (KWP.getElapsedTime() > KWPline)){
			//Если нажали ЛКМ,
			KWP.restart();
			//-----Eсли треугольников ещё не существует или мы создаём новую партию
			if (!polNo || newConv || triangle[polNo - 1].getOutlineThickness())
			{
				//t = true;
				if (clkm2==0)//на самый первый шелчёк
				{//достаём кисть
					convBrush = new sf::ConvexShape();
					convBrush->setPointCount(3);
					convBrush->setFillColor(sf::Color(0, 255, 123, 100));
					//и ставим первую вершину
					pointForS[0] = mouse;
				}
				if (clkm2 == 1)//на второй щелчёк 
				{
					//ставим вторую вершину
					pointForS[1] = mouse;
					for (int i = 0; i < 2; i++)//и устанавливаем их в треугольник-кисть
						convBrush->setPoint(i, pointForS[i]);
				}
				if (clkm2 == 2)//на третий щелчёк
				{
					pointForS[2] = mouse;//ставим последнюю вершину
					//t = true;
					//и отсылаем последнюю вершину в треугольник-кисть
					convBrush->setPoint(2, pointForS[2]);
					//рисуем
					triangle.push_back(*convBrush);
					//готовимся к тому, что в следующем треугольнике нас интересует только последняя вершина
					clkm2 = 1;
				}
				clkm2++;
				newConv = false;//можем только продолжать работать над созданной партией, а не создавать новую
			}
			//------Eсли уже существует хотябы один треугольник и мы продолжать
			if (polNo&&!triangle[polNo - 1].getOutlineThickness())
			{
				//то щелчёк уже полюбасу третий, т.е. clkm2=2, а значит
				if (clkm2 < 3 && clkm2 > 1)
				{
					//двумя первыми вершинами кисти для рисования нового треугольника принимаем две последние вершины последнего нарисованного 
					convBrush->setPoint(0, triangle[polNo - 1].getPoint(1));
					convBrush->setPoint(1, triangle[polNo - 1].getPoint(2));
					//если щелчёк третий, а он полюбасу третий,
					//то рисуем
					triangle.push_back(*convBrush);
					//и готовимся к тому, что в следующем треугольнике нас вновь интересует только последняя вершина
					clkm2 = 1;
					clkm2++;
				}
			}
		}
		if (clkm2 > 1)//если две вершины уже установлены
		{
			convBrush->setPoint(2, mouse);//то по def показываем, куда можно поставить последнюю вершину
			if (polNo&&!triangle[polNo - 1].getOutlineThickness())//а если треугольники ранее ещё были, значит мы продолжаем партию, т. е. newConv = false, т. е. другие вершины всё ещё на вершинах прошлого треугольника
			{
				convBrush->setPoint(0, triangle[polNo - 1].getPoint(1));
				convBrush->setPoint(1, triangle[polNo - 1].getPoint(2));
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && (KWP.getElapsedTime() > KWPline)&&clkm2>1)//Если ПКМ
		{
			//значит партия треугольников выпущена
			newConv = true;//и можно начинать новую
			KWP.restart();
			//значит рисуем последний треугольник в партии
			triangle.push_back(*convBrush);
			triangle[triangle.size() - 1].setFillColor(sf::Color(255, 106, 0, 100));
			triangle[triangle.size() - 1].setOutlineThickness(0.5f);
			//и складывем кисть, чтобы она не отображалась более
			delete convBrush;
			convBrush = NULL;
			clkm2 = 0;
		}
		break;
	////////////////////////////////////////////////////////////////////////////////////////////
	default:
		break;
	}
}

void CoolFigureEditor::draw()
{
	zoom = window->getView().getSize().x / WIDTH;
	sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f)*zoom + window->getView().getCenter();
	this->Mod3();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		center.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)) + sdvig);
	rectM.move(sdvig);
	circleM.move(sdvig);
	triangM.move(sdvig);
		window->draw(rectM);
		window->draw(circleM);
		window->draw(triangM);
	rectM.move(-sdvig);
	circleM.move(-sdvig);
	triangM.move(-sdvig);
	std::for_each(rect.begin(), rect.end(), [](sf::RectangleShape& r){ window->draw(r);});
	std::for_each(circle.begin(), circle.end(), [](sf::CircleShape& c){ window->draw(c);});
	std::for_each(triangle.begin(), triangle.end(), [](sf::ConvexShape& t){ window->draw(t);});
	window->draw(center);
	if (rectBrush != NULL) window->draw(*rectBrush);
	if (circleBrush != NULL) window->draw(*circleBrush);
	if (convBrush != NULL) window->draw(*convBrush);
}

void CoolFigureEditor::swUp()
{
	state++;
	if (state == 3) state = 0;
	updateMenuColor();
}
void CoolFigureEditor::swDown()
{
	state--;
	if (state == -1)state = 2;
	updateMenuColor();
}
void CoolFigureEditor::updateMenuColor()
{
	switch (state)
	{
	case 0:
		rectM.setFillColor(sf::Color(150, 0, 0, 100));
		circleM.setFillColor(sf::Color(255, 255, 255, 100));
		triangM.setFillColor(sf::Color(255, 255, 255, 100));
		break;
	case 1:
		circleM.setFillColor(sf::Color(150, 0, 0, 100));
		triangM.setFillColor(sf::Color(255, 255, 255, 100));
		rectM.setFillColor(sf::Color(255, 255, 255, 100));
		break;
	case 2:
		triangM.setFillColor(sf::Color(150, 0, 0, 100));
		rectM.setFillColor(sf::Color(255, 255, 255, 100));
		circleM.setFillColor(sf::Color(255, 255, 255, 100));
		break;
	default:
		break;
	}
}

CoolFigureEditor::~CoolFigureEditor()
{
}
