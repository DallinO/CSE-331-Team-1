#pragma once
#include "point.h"
#include "logicElement.h"
#include "interfaceElement.h"
#include <string>
#include <iostream>

using namespace std;

class StorageElement
{
protected:
	string type;
	Point pt;
	Velocity v;
	double radius;
	int points;
	bool dead;
	LogicElement* plogic;
	InterfaceElement* pInterface;
public:
	StorageElement(LogicElement* plogic, InterfaceElement* pInterface);
	string getType() { return type; }
	Point getPoint() { return pt; }
	Velocity getVelocity() { return v; }
	double getRadius() { return radius; }
	int getPoints() { return points; }
	bool isDead() { return dead; }
	LogicElement* getPLogic() { return plogic; }
	InterfaceElement* getPInterface() { return pInterface; }
};

class StorageBird : StorageElement
{
public:
	StorageBird(string type);
};

class StorageBullet : StorageElement
{
public:
	StorageBullet(string type);
};

class StorageEffect : StorageElement
{
private:
	double age;
public:
	StorageEffect(string type);
	double getAge() { return age; }
};
