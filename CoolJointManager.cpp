#include "CoolJointManager.h"
#include <iostream>
int							CoolJointManager::click(0);	 //цикл кликов
bool						CoolJointManager::kwp(false);//key was pressed
PrimitivBluePr*				CoolJointManager::pA(NULL);
PrimitivBluePr*				CoolJointManager::pB(NULL);
sf::RectangleShape			CoolJointManager::line[2];
float						CoolJointManager::zoom;
unsigned int				CoolJointManager::mustDie(0);
CoolMenu*					CoolJointManager::menu;
sf::RenderWindow*			CoolJointManager::window(NULL);
std::vector<JointBluePr>	CoolJointManager::joint;
sf::Text					CoolJointManager::str;

CoolJointManager::CoolJointManager()
{
}
CoolJointManager::CoolJointManager(sf::RenderWindow& w, CoolMenu* m)
{
	window = &w;
	menu = m;
	for (int i = 0; i < 2; i++)
	{
		line[i].setFillColor(sf::Color(100, 180, 200, 255));
		line[i].setOrigin(0, .5f);
		line[i].setPosition(0, 0);
		line[i].setSize({ 0, 1 });
	}
	JointBluePr::window = window;
}
bool isButtonChoosen(const sf::Vector2f& b,const sf::Vector2f& mouse)
{
	return (mouse.x>b.x&&mouse.x<b.x + 70.f&&mouse.y>b.y&&mouse.y < b.y + 20.f);
}
void CoolJointManager::coolSettingsWindow()//Не надо это читать
{
	sf::RectangleShape fon;
	sf::Vector2f camSize = window->getView().getSize(), center = window->getView().getCenter(), fonOrg = camSize*0.35f;
	fon.setPosition(center);
	fon.setSize(camSize*0.7f);
	fon.setOrigin(camSize*0.35f);
	fon.setFillColor(sf::Color(50, 50, 50, 255));
	bool br = false;//брэак-флаг
	int question = 0;
	int LimCount = 0;
	int SpAndFCount = 0;
	//----------------------------------------
	while (!br)
	{
		//----------------------------------------
		sf::Vector2f sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f)*zoom + window->getView().getCenter();
		sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*window))*zoom + sdvig;//курсор с учётом сдвига
		//----------------------------------------
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				br = true;
				joint.pop_back();
			}
		}
		//========================================
		//------Афанасий, я наговнокодил :D-------
		//========================================
		window->clear();
		window->draw(fon);
		//----------------------------------------
		bool LeftKey	= sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		bool RightKey	= sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		bool SpaceBar	= sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool VKey		= sf::Keyboard::isKeyPressed(sf::Keyboard::V) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		//----------------------------------------
		if (question == 0)//окно выбора типа
		{
			fon.move(.05f, 0.f);
			str.setPosition(center + sf::Vector2f(-0.5f*fonOrg.x, -0.5f*fonOrg.y));
			str.setStyle(0);
			str.setString("Choose type:");
			window->draw(str);
			setLiteButton("RevFree", center, fonOrg, -0.2f, -0.4f, mouse, question, 1, (joint.end() - 1)->type, 0);
			window->draw(str);
			setLiteButton("RevMotor", center, fonOrg, -0.2f, -0.1f, mouse, question, 3, (joint.end() - 1)->type, 1);
			window->draw(str);
			setLiteButton("ServoRev", center, fonOrg, -0.2f, 0.3f, mouse, question, 1, (joint.end() - 1)->type, 2);
			window->draw(str);
			setLiteButton("FreePrism", center, fonOrg, 0.4f, -0.4f, mouse, question, 1, (joint.end() - 1)->type, 3);
			window->draw(str);
			setLiteButton("PrismMotor", center, fonOrg, 0.4f, -0.1f, mouse, question, 4, (joint.end() - 1)->type, 4);
			window->draw(str);
			setLiteButton("ServoPrism", center, fonOrg, 0.4f, 0.3f, mouse, question, 1, (joint.end() - 1)->type, 5);
			window->draw(str);
		}
		//----------------------------------------
		if (question == 1)//окно принятия решения о использовании лимитов
		{
			fon.move(-.05f, 0.02f);
			str.setPosition(center + sf::Vector2f(-0.5f*fonOrg.x, -0.5f*fonOrg.y));
			str.setStyle(0);
			str.setString("Does it have a Limit?");
			window->draw(str);
			int type = (joint.end() - 1)->type;
			if (type == 0 || type == 2)//если rev
			{
				setLiteButton("Yes", center, fonOrg, 0.1f, -0.1f, mouse, question, 2, (joint.end()-1)->enableLimit, true);
				window->draw(str);
				setLiteButton("No", center, fonOrg, 0.1f, 0.3f, mouse, question, 5, br, true);
				window->draw(str);
			}
			if (type == 3 || type == 5)//если prism
			{
				setLiteButton("Yes", center, fonOrg, 0.1f, -0.1f, mouse, question, 2, (joint.end()-1)->enableLimit, true);
				window->draw(str);
				setLiteButton("No", center, fonOrg, 0.1f, 0.3f, mouse, question, 4, (joint.end()-1)->enableLimit, false);
				window->draw(str);
			}
			(joint.end()-1)->minl = 0.f;
			(joint.end()-1)->maxl = 0.f;
		}
		//----------------------------------------
		if (question == 2)//окно установки лимитов
		{
			fon.move(-.03f, -0.02f);
			str.setPosition(center + sf::Vector2f(-0.5f*fonOrg.x, -0.5f*fonOrg.y));
			str.setStyle(0);
			if ((joint.end() - 1)->type != 1 && (joint.end() - 1)->type != 4)
				str.setString("Limit of " + toString((joint.end() - 1)->type < 3 ? ((joint.end() - 1)->type == 0 ? "freeRevalue" : "ServoRev") : ((joint.end() - 1)->type == 3 ? "freePrismatic" : "ServoPrsm")) + "  " + toString(LimCount));
			window->draw(str);
			(joint.end() - 1)->drWithoutUpdates(center);
			sf::RectangleShape shMin, shMax, shNormal;
			shMin.setSize({ 50, 4 });
			shMax.setSize({ 50, 4 });
			shNormal.setSize({ 50, 4 });
			if ((joint.end()-1)->type == 0 || (joint.end()-1)->type == 2)//------------------------>revolue limit
			{//ебаааааать! Что это?! Что оно делает?! бляааа! Помогите!!!
				shMin.setFillColor(sf::Color::White);
				shMax.setFillColor(sf::Color::White);
				shMin.setPosition(center);
				shMax.setPosition(center);
				if (LimCount == 0)
				{
					if (LeftKey) (joint.end() - 1)->minl -= 0.4f;
					if (RightKey) (joint.end() - 1)->minl += 0.4f;
					if (SpaceBar)  (joint.end() - 1)->minl = 0.f;
					if (VKey) (joint.end() - 1)->minl = atan2f((mouse - center).y, (mouse - center).x)*s2dpl::RtoG - (joint.end() - 1)->getAAngle()+360;
					str.setPosition(center + sf::Vector2f(-0.5f*fonOrg.x, 0.5f*fonOrg.y));
					str.setString("<- <" + toString(float((joint.end()-1)->minl)) + "> ->\n    [F]-to enter");
					window->draw(str);
					shMin.setRotation((joint.end() - 1)->minl + (joint.end() - 1)->getAAngle());
					shMin.setFillColor(sf::Color::Red);
					window->draw(shMin);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) LimCount++;
				}
				if (LimCount == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::F))
					LimCount++;
				if (LimCount == 2)
				{
					if (LeftKey) (joint.end() - 1)->maxl -= 0.4f;
					if (RightKey) (joint.end() - 1)->maxl += 0.4f;
					if (SpaceBar)  (joint.end() - 1)->maxl = 0.f;
					if (VKey) (joint.end() - 1)->maxl = atan2f((mouse - center).y, (mouse - center).x)*s2dpl::RtoG - (joint.end() - 1)->getAAngle() + 360;
					str.setPosition(center + sf::Vector2f(-0.5f*fonOrg.x, 0.5f*fonOrg.y));
					str.setString('<' + toString(float((joint.end()-1)->minl)) + '>');
					window->draw(str);
					shMin.setRotation((joint.end() - 1)->minl + (joint.end() - 1)->getAAngle());
					window->draw(shMin);
					str.setPosition(center + sf::Vector2f(0.5f*fonOrg.x, 0.5f*fonOrg.y));
					str.setString("<- <" + toString(float((joint.end()-1)->maxl)) + "> ->\n    [F]-to enter\nor  [B]-to get back to \"min\" setting");
					window->draw(str);

					shMax.setRotation((joint.end() - 1)->maxl + (joint.end() - 1)->getAAngle());
					shMax.setFillColor(sf::Color::Red);
					window->draw(shMax);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
					{
						if ((joint.end()-1)->type == 2) question = 3;
						if ((joint.end()-1)->type == 0) br = true;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) LimCount=0;
				}
				str.setPosition(center + sf::Vector2f(-0.1f*fonOrg.x, 0.5f*fonOrg.y));
				str.setString("current angle=<" + toString((joint.end()-1)->angle)+'>');
				window->draw(str);
			}
			if ((joint.end() - 1)->type == 3 || (joint.end() - 1)->type == 5)//------------------------>prismatic limit
			{
				shNormal.setPosition(center);
				shMin.setFillColor(sf::Color::White);
				shMax.setFillColor(sf::Color::White);
				shMin.setPosition(center);
				shMax.setPosition(center);
				if (LimCount == 0)//set normal		готово
				{
					shMin.setSize({ 40, 4 });
					shMax.setSize({ 40, 4 });
					if (LeftKey) (joint.end() - 1)->normal -= 0.4f;
					if (RightKey) (joint.end() - 1)->normal += 0.4f;
					if (SpaceBar)  (joint.end() - 1)->normal = 0.f;
					if (VKey) (joint.end() - 1)->normal = atan2f((mouse - center).y, (mouse - center).x)*s2dpl::RtoG - (joint.end() - 1)->getAAngle() + 360;
					
					shNormal.setRotation((joint.end() - 1)->normal + (joint.end() - 1)->getAAngle());
					shNormal.setFillColor(sf::Color::Green);
					window->draw(shNormal);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) LimCount++;
				}
				if ((LimCount == 1 || LimCount == 3) && !sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !sf::Keyboard::isKeyPressed(sf::Keyboard::B))
					LimCount++;
				if (LimCount == 2)
				{
					if (LeftKey) (joint.end() - 1)->minl -= 0.5f;
					if (RightKey) (joint.end() - 1)->minl += 0.5f;
					if (SpaceBar)  (joint.end() - 1)->minl = 0.f;
					shNormal.setRotation((joint.end() - 1)->normal + (joint.end() - 1)->getAAngle());
					shNormal.setFillColor(sf::Color::Green);
					window->draw(shNormal);
					shMin.setRotation(shNormal.getRotation() + 90);
					shMin.setOrigin(shMin.getSize().x / 2, shMin.getSize().y / 2 + (joint.end() - 1)->minl);
					str.setPosition(center + sf::Vector2f(-0.5f*fonOrg.x, 0.5f*fonOrg.y));
					str.setString("<- <" + toString(float((joint.end() - 1)->minl)) + "> ->\n    [F]-to enter\nor  [B]-to get back to \"normal\" setting");
					window->draw(str);
					shMin.setFillColor(sf::Color::Red);
					window->draw(shMin);
					str.setPosition(center + sf::Vector2f(0.5f*fonOrg.x, 0.5f*fonOrg.y));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) LimCount++;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) LimCount = 0;
				}
				if (LimCount == 4)
				{
					if (LeftKey) (joint.end() - 1)->maxl -= 0.5f;
					if (RightKey) (joint.end() - 1)->maxl += 0.5f;
					if (SpaceBar)  (joint.end() - 1)->maxl = 0.f;
					shNormal.setRotation((joint.end() - 1)->normal + (joint.end() - 1)->getAAngle());
					shNormal.setFillColor(sf::Color::Green);
					window->draw(shNormal);
					shMax.setRotation(shNormal.getRotation() + 90);
					shMin.setRotation(shNormal.getRotation() + 90);
					shMax.setOrigin(shMax.getSize().x / 2, shMax.getSize().y / 2 + (joint.end() - 1)->maxl);
					shMin.setOrigin(shMin.getSize().x / 2, shMin.getSize().y / 2 + (joint.end() - 1)->minl);
					str.setPosition(center + sf::Vector2f(-0.5f*fonOrg.x, 0.5f*fonOrg.y));
					str.setString('<' + toString(float((joint.end() - 1)->minl)) + '>');
					window->draw(str);
					window->draw(shMin);
					str.setPosition(center + sf::Vector2f(0.5f*fonOrg.x, 0.5f*fonOrg.y));
					str.setString("<- <" + toString(float((joint.end() - 1)->maxl)) + "> ->\n    [F]-to enter\nor  [B]-to get back to \"min\" setting");
					window->draw(str);

					shMax.setFillColor(sf::Color::Red);
					window->draw(shMax);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
					{
						(joint.end() - 1)->normal = shNormal.getRotation();
						while ((joint.end() - 1)->normal < 0) (joint.end() - 1)->normal += 360.f;
						if ((joint.end() - 1)->type == 5) question = 3;
						if ((joint.end() - 1)->type == 3) br = true;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) LimCount = 1;
				}
				str.setPosition(center + sf::Vector2f(0.f*fonOrg.x, 0.5f*fonOrg.y));
				str.setString("Normal is:\n<- <" + toString((joint.end() - 1)->normal) + "> ->" + (LimCount == 0 ? "\n    [F]-to enter" : ""));
				window->draw(str);
			}
		}
		//----------------------------------------
		if (question == 3)//окно установки скорости и силы мотора
		{
			str.setPosition(center + sf::Vector2f(-0.5f*fonOrg.x, -0.5f*fonOrg.y));
			str.setStyle(0);
			if (SpAndFCount == 1)
			{
				if (LeftKey) (joint.end() - 1)->speed -= 0.4f;
				if (RightKey) (joint.end() - 1)->speed += 0.4f;
				if (SpaceBar) (joint.end() - 1)->speed  = 0.f;
				str.setString("Speed: <- <" + toString((joint.end() - 1)->speed) + "> ->\t\tpress [F]-to enter\n\nand\n\nForce: <" + toString((joint.end() - 1)->force) + '>');
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) SpAndFCount++;
			}
			if ((SpAndFCount == 2 || SpAndFCount == 0) && !sf::Keyboard::isKeyPressed(sf::Keyboard::F)) SpAndFCount++;
			if (SpAndFCount == 3)
			{
				if (LeftKey) (joint.end() - 1)->force -= 0.4f;
				if (RightKey) (joint.end() - 1)->force += 0.4f;
				if (SpaceBar) (joint.end() - 1)->force = 0.f;
				str.setString("Speed: <" + toString((joint.end() - 1)->speed) + ">\n\nand\n\nForce: <- <" + toString((joint.end() - 1)->force) + "> ->\n\tpress [F]-to continue\nor\npress [B]-to back to speed's setting");
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) br = true;
			}

			window->draw(str);
		}
		//----------------------------------------
		if (question == 4)
		{
			fon.move(-.03f, -0.02f);
			str.setPosition(center + sf::Vector2f(-0.5f*fonOrg.x, -0.5f*fonOrg.y));
			str.setStyle(0);
			if ((joint.end() - 1)->type != 1 && (joint.end() - 1)->type != 4)
				str.setString("Normal of " + std::string(((joint.end() - 1)->type) == 3 ? "freePrismatic" : "ServoPrsm") + "  " + toString(LimCount));
			window->draw(str);
			(joint.end() - 1)->drWithoutUpdates(center);
			sf::RectangleShape shNormal;
			shNormal.setSize({ 50, 4 });
			{/////////////////////////////////////
				shNormal.setPosition(center);
				if (LimCount == 0)
				{
					if (LeftKey) (joint.end() - 1)->normal -= 0.4f;
					if (RightKey) (joint.end() - 1)->normal += 0.4f;
					if (SpaceBar)  (joint.end() - 1)->normal = 0.f;
					if (VKey) (joint.end() - 1)->normal = atan2f((mouse - center).y, (mouse - center).x)*s2dpl::RtoG - (joint.end() - 1)->getAAngle() + 360;

					shNormal.setRotation((joint.end() - 1)->normal + (joint.end() - 1)->getAAngle());
					shNormal.setFillColor(sf::Color::Green);
					window->draw(shNormal);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) LimCount++;//LimCount==1
				}
				if ((LimCount == 1 || LimCount == 3) && !sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !sf::Keyboard::isKeyPressed(sf::Keyboard::B))
					LimCount++;
				if (LimCount == 2)
				{
					shNormal.setRotation((joint.end() - 1)->normal + (joint.end() - 1)->getAAngle());
					shNormal.setFillColor(sf::Color::Green);
					window->draw(shNormal);
					str.setPosition(center + sf::Vector2f(-0.5f*fonOrg.x, 0.5f*fonOrg.y));
					str.setString("<- <" + toString(float((joint.end() - 1)->minl)) + "> ->\n    [F]-to enter\nor  [B]-to get back to \"normal\" setting");
					window->draw(str);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
					{
						(joint.end() - 1)->normal = shNormal.getRotation();
						while ((joint.end() - 1)->normal < 0) (joint.end() - 1)->normal += 360.f;
						if ((joint.end() - 1)->type == 4 || (joint.end() - 1)->type == 5) question = 3;
						if ((joint.end() - 1)->type == 3) br = true;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) LimCount = 1;
				}
				str.setPosition(center + sf::Vector2f(0.f*fonOrg.x, 0.5f*fonOrg.y));
				str.setString("Normal is:\n<- <" + toString((joint.end() - 1)->normal) + "> ->" + (LimCount == 0 ? "\n    [F]-to enter" : ""));
				window->draw(str);
			}/////////////////////////////////////
		}
		//----------------------------------------
		window->display();
	}
}
void CoolJointManager::newJointCreation(sf::Vector2f& mouse)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !kwp && PrimitivBluePr::chosen != NULL)
	{
		kwp = true;
		if (click == 2)
		{
			joint.push_back(JointBluePr(pA, pB, mouse));
			pA = NULL;
			pB = NULL;
			click = 0;
			CoolMenu::state = 0;
			coolSettingsWindow();
			menu->setZeroState();
		}
		if (click == 1 && PrimitivBluePr::chosen != pA)
		{
			pB = PrimitivBluePr::chosen;
			click++;
		}
		if (CoolMenu::state == 4 && click == 0)
		{
			pA = PrimitivBluePr::chosen;
			click++;
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) kwp = false;

}
void CoolJointManager::draw()
{
	//Cдвиг камеры относительно центра размера окна
	zoom = window->getView().getSize().x / WIDTH;
	sf::Vector2f sdvig = -sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f)*zoom + window->getView().getCenter();
	sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*window))*zoom + sdvig;//курсор с учётом сдвига
	{//отрисовка и удаление соединений
		static unsigned int mbe = 0;
		std::for_each(joint.begin(), joint.end(), [](JointBluePr& j){ j.draw(); mbe++; if (j.mustToBeErased)mustDie = mbe; });
		if (mustDie != 0)	joint.erase(joint.begin()+mustDie - 1);
		mbe = 0; mustDie=0;
	}

	if (CoolMenu::state == 4)
	{
		std::cout << click << std::endl;
		newJointCreation(mouse);
		for (int i = 0; i < click; i++)
		{
			const sf::Vector2f v = (i == 0 ? pA : pB)->getPosition() - mouse;
			float l = sqrt(v.x*v.x + v.y*v.y);
			line[i].setPosition(mouse);
			line[i].setSize({ l, 1 });
			line[i].setRotation(std::atan2f(v.x, -v.y) * 57.2958f - 90.f);
			window->draw(line[i]);
		}
	}
}
CoolJointManager::~CoolJointManager()
{
}
