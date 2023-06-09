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
	static Point dimensions;
	string type;
	Point pt;
	Velocity v;
	double radius;
	int points;
	bool dead;
public:
	StorageElement();
	string getType() { return type; }
	Point getPoint() { return pt; }
	Velocity getVelocity() { return v; }
	double getRadius() { return radius; }
	int getPoints() { return points; }
	bool isDead() { return dead; }
	Point getDimensions() { return dimensions; }
};

class BulletStorage : public StorageElement
{
private:
	int timeToDie;
public:
	int getTimeToDie() { return timeToDie; }
	void setTimeToDie(int value) { timeToDie = value; }
};

class StorageEffect
{
private:
	Point pt;
	Velocity v;
	double size;
	double age;
	Point ptEnd;
public:
	StorageEffect(string type);
	Point getPoint() { return pt; }
	double getAge() { return age; }
	double getSize() { return size; }
	Velocity getV() { return v; }
	Point getPtEnd() { return ptEnd; }
};

class UserInputStorage
{

};

enum ElementType
{
	Bird,
	Bullet,
};