#ifndef S2DPLCONTACTLISTENNER_H
#define S2DPLCONTACTLISTENNER_H
#include <vector>
#include <string>
#include "Box2D\Box2D.h"
#include "Sensor.h"

class s2dplContactListenner :
	public b2ContactListener
{
private:
	//static std::string sepor(std::string strr, std::string by, int n);
	static std::string usrstr;
public:
	s2dplContactListenner();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	~s2dplContactListenner();
};


#endif