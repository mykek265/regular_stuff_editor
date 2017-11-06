#include "s2dplContactListenner.h"
#include "Sensor.h"
#include <string.h>
#include <iostream>

std::string s2dplContactListenner::usrstr;
/*������� ��� ���������� ������ �� ������-������ ��������(� �������, ����� �������)
�� ��������� ������� � ���������� ������ �������� �������, ���� ����� ����*/
std::string sepor(const std::string& strr, const std::string& by, int n)
{
	std::vector<std::string> arr;
	std::string str = strr;
	std::string delim = by;
	size_t prev = 0;
	size_t next;
	size_t delta = delim.length();

	while ((next = str.find(delim, prev)) != std::string::npos){
		//�������-start
		std::string tmp = str.substr(prev, next - prev);
		//�������-end
		arr.push_back(str.substr(prev, next - prev));
		prev = next + delta;
	}
	//�������-start
	std::string tmp = str.substr(prev);
	//�������-end
	arr.push_back(str.substr(prev));
	if (n<(int)arr.size()) return arr[n];
	else return NULL;
}


s2dplContactListenner::s2dplContactListenner()
{
}
s2dplContactListenner::~s2dplContactListenner()
{
}



void s2dplContactListenner::BeginContact(b2Contact* contact)
{	
	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetUserData();
	if (bodyUserData)
		if (static_cast<std::string*>(bodyUserData))
		{
			std::string usrstr0 = *(static_cast<std::string*>(bodyUserData));
			if (sepor(usrstr0, ",", 0) == "sensor")
			{
				//int at = std::atoi(sepor(usrstr0, ",", 1).c_str());
				s2dpl::Sensor::sensor[usrstr0]->startContact();
			}
		}

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetUserData();
	if (bodyUserData)
		if (static_cast<std::string*>(bodyUserData))
		{
			std::string usrstr0 = *(static_cast<std::string*>(bodyUserData));
			if (sepor(usrstr0, ",", 0) == "sensor")
			{
				//int at = std::atoi(sepor(usrstr0, ",", 1).c_str());
				s2dpl::Sensor::sensor[usrstr0]->startContact();
			}
		}
}


void s2dplContactListenner::EndContact(b2Contact* contact)
{
	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetUserData();
	if (bodyUserData)
		//if (static_cast<std::string*>(bodyUserData))
		{
			std::string usrstr0 = *(static_cast<std::string*>(bodyUserData));
			if (sepor(usrstr0, ",", 0) == "sensor")
			{
				s2dpl::Sensor::sensor[usrstr0]->endContact();//����� - ��� ����� ������� � ������ ��������(���������� ������� �� ����� ������, �.�. �������� ��� �� �������, � ������ �� �� �����, �������)
			}
		}

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetUserData();
	if (bodyUserData)
		//if (static_cast<std::string*>(bodyUserData))
		{
			std::string usrstr0 = *(static_cast<std::string*>(bodyUserData));
			if (sepor(usrstr0, ",", 0) == "sensor")
			{
				s2dpl::Sensor::sensor[usrstr0]->endContact();
			}
		}
}


//void s2dplContactListenner::EndContact(b2Contact* contact)
//{
//	//check if fixture A was a ball
//	void* bodyUserData = contact->GetFixtureA()->GetUserData();
//	if (static_cast<std::string*>(bodyUserData))
//		if (sepor(*(static_cast<std::string*>(bodyUserData)), ",", 0) == "sensor")//������, ��� ��� �������� ����� ������, ���� ��, ��� �����
//		{
//			int number = atoi(s2dplContactListenner::sepor(*(static_cast<std::string*>(bodyUserData)), ",", 1).c_str());//�� ����� ����� � ������
//			//			(s2dpl::Sensor::sensorid[number])->endContact();
//		}
//
//	//check if fixture B was a ball
//	bodyUserData = contact->GetFixtureB()->GetUserData();
//	if (static_cast<std::string*>(bodyUserData))
//		if (sepor(*(static_cast<std::string*>(bodyUserData)), ",", 0) == "sensor")//������, ��� ��� �������� ����� ������, ���� ��, ��� �����
//		{
//			int number = atoi(s2dplContactListenner::sepor(*(static_cast<std::string*>(bodyUserData)), ",", 1).c_str());//�� ����� ����� � ������
//			//		(s2dpl::Sensor::sensorid[number])->endContact();
//		}
//}



