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
public:
	StorageEffect(string type);
};
