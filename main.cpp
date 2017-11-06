#include "s2dpl.h"
#include <iostream>
#include <vector>
#include <string> 
//#include <sstream>
//------------------------------------------------
#include "windowSize.h"//константы
//#include "sfButton.h"					//работает (костыль)
#include "CoolMenu.h"					//работает
#include "CoolScrollBar.h"				//работает
#include "CoolFigureEditor.h"			//работает
#include "CoolFeatureWindow.h"			//работает (можно сделать более чувствительную подстройку для коэффициентов)
#include "PrimitivBluePr.h"				//работает
#include "CoolJointManager.h"			//работает (самая потная хрень была)
#include "GreatTestManager.h"			//работает
#include "CoolImageManager.h"			//работает (на поворачивании баг. что с ним делать не знаю.)
#include "coolSensorManager.h"			//работает
#include "Saver.h"//				<=============сделать

//------------------------------------------------
using namespace std;
//------------------------------------------------
sf::Font				mainFont;
sf::Text				str1, str2;
sf::View				cam1;
sf::Sprite				fon;
//vector<sfButton>		button;
vector<PrimitivBluePr>	bluePrint;
CoolMenu*				menu;
CoolScrollBar			scrollBar;
CoolFigureEditor		figEditor;
CoolJointManager		jEditor;
CoolFeatureWindow		partWindow;
GreatTestManager		testManager;
CoolImageManager		imgManager;
coolSensorManager		sensManager;
Saver					mySaver;

float ZOOM = 1;
//////////////////////////////////////////////////
//------------------------------------------------
void Load(sf::RenderWindow& window, b2World& world, sf::Vector2f& mouse)
{
	window.setFramerateLimit(70);
	world.SetContactListener(&s2dpl::myContactListener);
	cam1.setSize(sf::Vector2f(window.getSize()));
	//--------------------------------
	//---Подготовка главного шрифта---
	//--------------------------------
	mainFont.loadFromFile("10506.ttf");
	menu = new CoolMenu(window, mainFont);
	scrollBar = CoolScrollBar(window);
	figEditor = CoolFigureEditor(window);
	str1.setFont(mainFont);
	str1.setColor(sf::Color(216, 170, 41,255));
	str1.setCharacterSize(14);
	//---Унификация всех шрифтов---*
	str2 = str1;
	PrimitivBluePr::characteristics = str1;
	PrimitivBluePr::characteristics.setColor(sf::Color(100, 255, 100, 255));
	JointBluePr::characteristics = str1;
	JointBluePr::characteristics.setColor(sf::Color(216, 170, 41, 255));
	CoolJointManager::str = str1;
	CoolJointManager::str.setColor(sf::Color(216, 170, 41, 255));
	s2dpl::Sensor::init(world, window);
	//----Установка своего фона----*
	static sf::Texture fonT;
	fonT.loadFromFile("img/fon.png");
	fon.setTexture(fonT);
	//-----------------------------*
	//if (fullscrin) 
	//	button.push_back(sfButton(sf::Color(105, 0, 0, 225), sf::Color::Red, { 25, 25 }, { 1320, 10 }, "X", mainFont, 24));
	//-----------------------------*
	jEditor = CoolJointManager(window, menu);
	partWindow = CoolFeatureWindow(window, mainFont);
	testManager = GreatTestManager(window, world);
	imgManager = CoolImageManager(window, scrollBar, menu);
	sensManager = coolSensorManager();
	sensManager.ppr = &bluePrint;
	mySaver = Saver(window, cam1, mouse, str1, bluePrint, jEditor);
	//-----------------------------*
	SensorBpr::window = &window;
	//-----------------------------*
	menu->addButton(std::string("AddFigure"), 14);		 //state 1
	menu->addButton(std::string("AddImagesTo..."), 14);	 //state 2
	menu->addButton(std::string("AddSensorTo..."), 14);	 //state 3
	menu->addButton(std::string("AddJointTo..."), 14);	 //state 4
	menu->addButton(std::string("StartSimulation"), 14); //state 5
	menu->addButton(std::string("SaveStuff"), 14);		 //state 6
}
//------------------------------------------------
inline void controlState1();
inline void controlState5();
inline void controlState6();
void controlView(sf::RenderWindow& window);
void pushBPart();
//////////////////////////////////////////////////
int main()
{
	//------------------------------------------------
	/*--Инициализация--*/
		/*--окна--*/
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cool Stuff Editor", (fullscrin?sf::Style::Fullscreen:sf::Style::Default), settings);
		/*--мира--*/
	b2World world(b2Vec2(0, -9.832f));
		/*--и всего
		остального--*/
	sf::Vector2f mouse;
	std::string display;
	Load(window, world, mouse);
	//------------------------------------------------
	//Баловство
	//sf::Vector2f v3[3] = { { 10, 10 }, { 0, -110 }, { -10, 10 } }, bpos;
	//s2dpl::Triangle triangle(world, window, cam1.getCenter().x, cam1.getCenter().y, v3, 1);
	//s2dpl::Box box(world, window, bpos=cam1.getCenter(), { 300, 50 }, 0);
	//box.addSensor({ -20, -20 }, { 10, 10 });
	//triangle.addSensor({ 5, -250 }, { 20, 20 });
	//s2dpl::RevJoint* myJoint= new s2dpl::ServoRevJoint(&world, triangle, box, { 0, 20 }, {0,-20});
	//std::auto_ptr<s2dpl::RevJoint>jjj(myJoint);
	//myJoint->setSpeedForce(2, 320);
	//sf::Texture t;
	//------------------------------------------------
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed/*||button[0].draw(window,mouse)*/)
			{
				event.type = sf::Event::Closed;
				if (testManager.work)
					testManager.stop();
				delete menu;
				window.close();
			}
			/*--Прокручивание колеса--*/
			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					if (event.mouseWheel.delta < 0)//вверх
					{
						if (menu->state == 1)
							figEditor.swUp();
						if (menu->state == 2)
						{
							scrollBar.scrUp();
							imgManager.scrUp();
						}
					}
					if (event.mouseWheel.delta > 0)//вниз
					{
						if (menu->state == 1)
							figEditor.swDown();
						if (menu->state == 2)
						{
							scrollBar.scrDown();
							imgManager.scrDown();
						}
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					if (event.mouseWheel.delta < 0)//вверх
					{
						ZOOM += .01f;
					}
					if (event.mouseWheel.delta > 0)//вниз
					{
						ZOOM -= .01f;
					}
				}
			}
			/*--Ввод текста--*/
			if (CoolMenu::state == 6)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode >= 33 && event.text.unicode <= 126)
						display += (char)event.text.unicode;
					else if (event.text.unicode == 8)
						display = display.substr(0, display.length() - 1);
					mySaver.enterName(display);
				}
			}
		}
		world.Step(1 / 60.f, 8, 3);
		mouse = (sf::Vector2f(sf::Mouse::getPosition(window)) - sf::Vector2f(window.getSize().x *0.5f, window.getSize().y *0.5f))*(cam1.getSize().x / WIDTH )+ cam1.getCenter();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) cam1.setSize(WIDTH, HEIGHT);
		controlView(window);

//		float a = (atan2f(mouse.y - bpos.y, mouse.x - bpos.x)*s2dpl::RtoG);
		{////////////////////////Как-бы консольная строка
			str1.setPosition(-sf::Vector2f(window.getSize().x*0.5f, window.getSize().y*0.5f) + cam1.getCenter());

			str1.setString(
				/*toString(a>0?a:360+a) +*/
				"\nStuff Editor " + toString(menu->state) + "\ncamera(" + toString(cam1.getCenter().x) + ", " + toString(cam1.getCenter().y) + ")(" + toString(cam1.getSize().x) + ", " + toString(cam1.getSize().y) + ")\n" +
				"mouse(" + toString(mouse.x) + ", " + toString(mouse.y) + ")"
				);

			if (menu->state == 1)
				str1.setString(
					str1.getString() +
					"\nRectangles: " + toString(figEditor.rect.size()) +
					"\nCircles: " + toString(figEditor.circle.size()) +
					"\nTriangles: " + toString(figEditor.triangle.size())
					);
			if (menu->state == 2)
				str1.setString(
				str1.getString() +
				"\nTexture No " + toString(scrollBar.Nimg)
				);
			
		}///////////////////////////////////////////////
//		myJoint->setAngle((a>0?a:360+a)+90);
		////////////////////////////////////////////////
		cam1.zoom(ZOOM);
		ZOOM = 1;
		window.setView(cam1);
		window.clear();
		window.draw(fon);
		window.draw(str1);
		if (menu->state!=5)
			jEditor.draw();
		if (CoolMenu::state == 1)
		{
			figEditor.draw();
		}
		if (CoolMenu::state == 2)
		{
			imgManager.draw();
			scrollBar.draw();
		}
		if (CoolMenu::state == 3)
			sensManager.draw();
		if (menu->state!=5)
			for (unsigned int i = 0; i < bluePrint.size(); i++)
			{
				if (bluePrint[i].draw() == &bluePrint[i])
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
						bluePrint.erase(bluePrint.begin()+i);
				}
			}
		if (CoolMenu::state == 5)
			controlState5();
		if (CoolMenu::state == 6)
			controlState6();
		menu->draw();
		/*if (fullscrin)
			if (button[0].draw(window, mouse))
			{ 
				if(testManager.work)
					testManager.stop();
				//delete menu;
			}*/
		if (CoolFeatureWindow::active)
		{
			short a=partWindow.draw();
			if (a==1||a==2)
			{
				if (a == 1) bluePrint.push_back(PrimitivBluePr(	window, figEditor, partWindow));
				figEditor.rect.clear();
				figEditor.circle.clear();
				figEditor.triangle.clear();
				CoolFeatureWindow::active = false;
			}
		}
//		box.draw();
//		triangle.draw();
		window.display();
	}
	
	return 0;
}

//Управ. кнопками 
void controlView(sf::RenderWindow& window)
{
	const float speed = 0.8f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))	cam1.move(-speed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))	cam1.move(speed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))	cam1.move(0.f, -speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))	cam1.move(0.f, speed);
	if (menu->state == 1)	controlState1();
}


inline void controlState1()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		menu->setZeroState();
		CoolFeatureWindow::active = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		menu->setZeroState();
		figEditor.center.setPosition(0.f, 0.f);
		figEditor.rect.clear();
		figEditor.circle.clear();
		figEditor.triangle.clear();
	}
}
inline void controlState5()
{
	if (!testManager.work)
	{
		std::cout << "Test begines" << std::endl;
		testManager.load(bluePrint, jEditor);
		testManager.work = true;
	}

	testManager.draw();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		menu->setZeroState();
		if(testManager.work)
			testManager.stop();
	}
}
inline void controlState6()
{
	mySaver.draw();
	if (Saver::_state != 0)
	{
		if (Saver::_state == 1)
		{
			std::cout << "Sohranenie nachato!" << std::endl;
			mySaver.save();
			mySaver.save_plus();
		}
		menu->setZeroState();
		Saver::_state = 0;
	}
}