#ifndef COOLSENSORMANAGER_H
#define COOLSENSORMANAGER_H
#include "SensorBpr.h"
#include "PrimitivBluePr.h"
#include <vector>

class coolSensorManager
{
private:
	std::vector<SensorBpr> sensor;
	float zoom;
	static sf::Vector2f sdvig, mouse;
	static sf::RectangleShape line, rect;
	static PrimitivBluePr* curPrm;
	static bool ch;
	//static float r;
	//static sf::Vector2f v;
	bool bwp;
	int countP;
public:
	std::vector<PrimitivBluePr>* ppr;
	static std::vector<PrimitivBluePr>* bpr;
	coolSensorManager();
	~coolSensorManager();
	void draw();
};
#endif
