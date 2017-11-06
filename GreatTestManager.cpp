#include <algorithm>
#include <map>
#include "GreatTestManager.h"
#include "S2DPL\Box.h"
std::vector<s2dpl::Primitiv*>	GreatTestManager::primitiv;
std::vector<s2dpl::RevJoint*>	GreatTestManager::revjoint;
std::vector<s2dpl::PrismJoint*>	GreatTestManager::prismjoint;
sf::RenderWindow*				GreatTestManager::window;
b2World*						GreatTestManager::world;
std::vector<PrimitivBluePr>*	GreatTestManager::blpr;

GreatTestManager::GreatTestManager()
	:work(false)
{
}
GreatTestManager::GreatTestManager(sf::RenderWindow& lwindow, b2World& lworld)
	: work(false)
{
	window = &lwindow;
	world = &lworld;
}
void GreatTestManager::loadSpr(std::vector<sf::Sprite>::iterator& begin, int size)
{
	for (int i = 0; i < size; i++)
		(*(primitiv.end() - 1))->addImg(*(begin+i));
}
s2dpl::Primitiv* GreatTestManager::lload(PrimitivBluePr& blueprint)//��������� �������
{
	work = true;
	//-----------------------------------------------------
	//----------����������� ������ �� ����� �����----------
	//-----------------------------------------------------
	const int						 type = blueprint.getType();
	std::vector<sf::RectangleShape>& rect = blueprint.getRects();
	std::vector<sf::CircleShape>&	 circ = blueprint.getCircles();
	std::vector<sf::ConvexShape>&	 triang = blueprint.getTriangles();
	std::vector<SensorBpr>			 sensor = (*blueprint.getSensor());
	uint16							 im = blueprint.getMyBits();
	uint16							 icol = blueprint.getColideBits();
	float							 density = blueprint.getDensity();
	float							 friction = blueprint.getFriction();
	float							 elasticity = blueprint.getElasticity();
	unsigned int size[3] = { rect.size(), circ.size(), triang.size() };
	///////////////////////////////////////////////////////
	//----�� ������, ���� ����� ����� �������
	//-----------------------------------------------------
	if (size[0] == 1 && size[1] == 0 && size[2] == 0)//������ �������
	{
		sf::Vector2f sv2(rect[0].getSize()*0.5f);

		primitiv.push_back(new s2dpl::Box(*world, *window, blueprint.getPosition() + rect[0].getPosition() + sv2, sv2, density, friction, elasticity, type, im, icol));
		//--------��������� �������� � ���������� (�� ���������) ���������
		loadSpr(blueprint.getImages()->begin(), blueprint.getImages()->size());
		//--------��������� ������� � ���������� (�� ���������) ���������
		for (int i = 0; i < sensor.size(); i++)
			primitiv[primitiv.size() - 1]->addSensor(sensor[i].getPosition(), sensor[i].getSize());
		//-------���������� ������ �� ��������� ��������-------
		return *(primitiv.end()-1);
	}
	//-----------------------------------------------------
	if (size[0] == 0 && size[1] == 1 && size[2] == 0)//������ ����
	{
		float r = circ[0].getRadius();
		primitiv.push_back(new s2dpl::Circle(*world, *window, blueprint.getPosition() + circ[0].getPosition(), r, type));
		
		//--------��������� ��������
		loadSpr(blueprint.getImages()->begin(), blueprint.getImages()->size());
		//--------��������� �������
		for (int i = 0; i < sensor.size(); i++)
			primitiv[primitiv.size() - 1]->addSensor(sensor[i].getPosition(), sensor[i].getSize());
		//-------���������� ������ �� ��������� ��������-------
		return *(primitiv.end()-1);
	}
	//-----------------------------------------------------
	if (size[0] == 0 && size[1] == 0 && size[2] == 1)//������ �����������
	{
		sf::Vector2f v3[3] = { triang[0].getPoint(0), triang[0].getPoint(1), triang[0].getPoint(2) };
		primitiv.push_back(new s2dpl::Triangle(*world, *window, blueprint.getPosition() + triang[0].getPosition() - triang[0].getOrigin(), v3, type));
		
		//--------��������� ��������
		loadSpr(blueprint.getImages()->begin(), blueprint.getImages()->size());
		//--------��������� �������
		for (int i = 0; i < sensor.size(); i++)
			primitiv[primitiv.size() - 1]->addSensor(sensor[i].getPosition(), sensor[i].getSize());
		//-------���������� ������ �� ��������� ��������-------
		return *(primitiv.end()-1);
	}
	///////////////////////////////////////////////////////
	//----�� ������, ���� ����� ���������
	//-----------------------------------------------------
	//--------�������� ��� �����
	s2dpl::Primitiv* prim = new s2dpl::Primitiv(*world, *window, blueprint.getCenter(), type); 
	//--------��������� �������
	for (int i = 0; i < rect.size(); i++)
		prim->addRect(rect[i].getPosition() + rect[i].getSize()*0.5f, rect[i].getSize()*0.5f, density, friction, elasticity);
	//--------��������� ����
	for (int i = 0; i < circ.size(); i++)
		prim->addCirc(circ[i].getPosition(), circ[i].getRadius());
	//--------��������� �����������
	sf::Vector2f ppos;
	for (int i = 0; i < triang.size(); i++)
	{
		sf::Vector2f v3[3] = { triang[i].getPoint(0), triang[i].getPoint(1), triang[i].getPoint(2) };
		ppos = triang[i].getPosition()-triang[i].getOrigin();
		prim->addTriang(ppos, v3);
	}
	primitiv.push_back(prim);
	//--------��������� ��������
	loadSpr(blueprint.getImages()->begin(), blueprint.getImages()->size());
	//--------��������� �������
	for (int i = 0; i < sensor.size(); i++)
		primitiv[primitiv.size() - 1]->addSensor(sensor[i].getPosition(), sensor[i].getSize());
	//-----------------------------------------------------
	//-------���������� ������ �� ��������� ��������-------
	//-----------------------------------------------------
	return *(primitiv.end()-1);
}
void GreatTestManager::load(std::vector<PrimitivBluePr>& blueprint, CoolJointManager& manager)
{
	work = true;
	blpr = &blueprint;
	sf::Vector2f posA, posB;
	std::map<PrimitivBluePr*,s2dpl::Primitiv*> usedPrim;
	//----------��������� ���������� � �����, ������� ��� ���������--------------
	for (unsigned int i = 0; i < manager.joint.size(); i++)
	{
		//��������� �����
		posA = manager.joint[i].getPosition() - manager.joint[i].primitivA->getPosition();
		posB = manager.joint[i].getPosition() - manager.joint[i].primitivB->getPosition();
		//=================================================
		//-----������ ����� ������� ����� ���������--------
		//=================================================
		s2dpl::Primitiv *A, *B;
		if (!usedPrim.count(manager.joint[i].primitivA))
		{
			A = lload(*manager.joint[i].primitivA);
			usedPrim.insert(std::make_pair(manager.joint[i].primitivA,A));
		}
		else
			A = usedPrim[manager.joint[i].primitivA];
		//-------------------------------------------------
		if (!usedPrim.count(manager.joint[i].primitivB))
		{
			B = lload(*manager.joint[i].primitivB);
			usedPrim.insert(std::make_pair(manager.joint[i].primitivB, B));
		}
		else
			B = usedPrim[manager.joint[i].primitivB];
		//-------------------------------------------------
		manager.joint[i].primitivA->loaded = true;
		manager.joint[i].primitivB->loaded = true;
		//=================================================
		//--------------������ ����������------------------
		//=================================================
		if (manager.joint[i].type == 0)//free RevJoint
		{
			revjoint.push_back(new s2dpl::RevJoint(world, *A, *B, posA, posB));
			if (manager.joint[i].enableLimit)
				(*(revjoint.end() - 1))->onLimit(manager.joint[i].minl, manager.joint[i].maxl);
		}
		//-------------------------------------------------
		if (manager.joint[i].type == 1)//RevJoint with Motor
		{
			revjoint.push_back(new s2dpl::RevJoint(world, *A, *B, posA, posB));
			(*(revjoint.end() - 1))->onMotor(manager.joint[i].speed, manager.joint[i].force);
		}
		//-------------------------------------------------
		if (manager.joint[i].type == 2)//ServoRevJoint
		{
			revjoint.push_back(new s2dpl::ServoRevJoint(world, *A, *B, posA, posB));
			(*(revjoint.end() - 1))->setSpeedForce(manager.joint[i].speed, manager.joint[i].force);
			(*(revjoint.end() - 1))->setAngle(manager.joint[i].getAAngle());
		}
		//=================================================
		if (2 < manager.joint[i].type)
		{
			sf::Vector2f normal = sf::Vector2f(std::cosf(manager.joint[i].normal*s2dpl::GtoR), std::sinf(manager.joint[i].normal*s2dpl::GtoR));
			if (manager.joint[i].type == 3)//free PrismaticJoint
			{
				prismjoint.push_back(new s2dpl::PrismJoint(world, *A, *B, posA, posB, normal));
				if (manager.joint[i].enableLimit)
					(*(prismjoint.end() - 1))->onLimit(manager.joint[i].minl, manager.joint[i].maxl);
			}
			//-------------------------------------------------
			if (manager.joint[i].type == 4)//PrismaticJoint with Motor
			{
				prismjoint.push_back(new s2dpl::PrismJoint(world, *A, *B, posA, posB, normal));
				(*(prismjoint.end() - 1))->onMotor(manager.joint[i].speed, manager.joint[i].force);
			}
			//-------------------------------------------------
			if (manager.joint[i].type == 5)//ServoPrismaticJoint
			{
				prismjoint.push_back(new s2dpl::ServoPrismJoint(world, *A, *B, posA, posB, normal));
				(*(prismjoint.end() - 1))->setSpeedForce(manager.joint[i].speed, manager.joint[i].force);
				(*(prismjoint.end() - 1))->setDistance(0.f);
			}
		}
	}
	usedPrim.clear();
	//===========================================================
	//-----------------��������� ��������� �����-----------------
	//===========================================================
	for (unsigned int i = 0; i < blueprint.size(); i++)
	{
		if (!blueprint[i].loaded)
			lload(blueprint[i]);
		if (blueprint[i].loaded)
			blueprint[i].loaded = false;
	}
}
void GreatTestManager::draw()
{
	std::for_each(primitiv.begin(), primitiv.end(), [](s2dpl::Primitiv* pr){pr->draw();});
}
void GreatTestManager::stop()
{
	work = false;

	std::for_each(blpr->begin(), blpr->end(), [](PrimitivBluePr& pbp){ pbp.loaded = false; });

	std::cout << "Here was " << primitiv.size() << " primitivs in test" << std::endl;
	for (unsigned int i = 0; i < primitiv.size(); i++)
		world->DestroyBody(primitiv[i]->physics);
	primitiv.clear();
	std::cout << "And now here is " << primitiv.size() << " primitivs" << std::endl;
	if (!work)
	std::cout << "work is end" << std::endl;
}
GreatTestManager::~GreatTestManager()
{
	for (unsigned int i = 0; i < revjoint.size(); i++)
		revjoint[i]->~RevJoint();
	for (unsigned int i = 0; i < primitiv.size(); i++)
	{
		world->DestroyBody(primitiv[i]->physics);
		primitiv[i]->~Primitiv();
	}
	primitiv.clear();
}
