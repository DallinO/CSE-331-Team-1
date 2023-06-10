#pragma once
#include "point.h"
#include "enums.h"
#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

#define FRAMES_PER_SECOND 30

class StorageElement
{
protected:
	static Point dimensions;
	Element type;
	Point pt;
	Velocity v;
	double radius;
	int points;
	bool dead;
public:
	StorageElement();
	Element getType() { return type; }
	Point getPoint() { return pt; }
	Velocity getVelocity() { return v; }
	double getRadius() { return radius; }
	int getPoints() { return points; }
	bool isDead() { return dead; }
	Point getDimensions() { return dimensions; }

	void kill() { dead = true; }
	void setVelocity(Velocity v) { this->v = v; }
	void setPoints(int value) { points = value; }
};

class BirdStorage : public StorageElement
{
public:
	BirdStorage(Element type, double radius, double speed, int points, double y)
	{
		pt.setY(y);
		pt.setX(0.0);
		// set the velocity
		v.setDx(randomFloat(speed - 0.5, speed + 0.5));
		v.setDy(randomFloat(-speed / 5.0, speed / 5.0));
		// set the points
		this->points = points;
		// set the size
		this->radius = radius;
		this->type = type;
	}
};

class BulletStorage : public StorageElement
{
private:
	int timeToDie;
public:
	// shrpnel constructor
	BulletStorage(Element type, BulletStorage& bomb)
	{
		this->type = type;
		timeToDie = random(5, 15);

		// The speed and direction is random
		v.set(random(0.0, 6.2), random(10.0, 15.0));
		pt = bomb.getPoint();

		radius = 3.0;
	}
	// defualt constructor
	BulletStorage(Element type, double angle)
	{
		double speed;
		switch (type)
		{
			case Missle:
				radius = 1.0;
				points = 3;
				speed = 10;
				break;
			case Bomb:
				radius = 4.0;
				points = 4;
				speed = 10;
				break;
			case Pellet:
				radius = 4.0;
				points = 4;
				speed = 15;
				break;
		}
		dead = false;
		pt.setX(dimensions.getX() - 1.0);
		pt.setY(1.0);
		assert(pt.getX() > 100.0);

		// set the initial velocity
		v.setDx(-speed * cos(angle));
		v.setDy(speed * sin(angle));
		assert(v.getDx() <= 0.0);
		assert(v.getDy() >= 0.0);
	}
	int getTimeToDie() { return timeToDie; }
	void setTimeToDie(int value) { timeToDie = value; }
};

class StorageEffect
{
private:
	Element type;
	Point pt;
	Velocity v;
	double size;
	double age;
	Point ptEnd;
public:
	// Defualt Contructor
	StorageEffect(Element type, Point pt, Velocity v)
	{
		ptEnd = pt;
		v *= -1.0;
		ptEnd += v;
		age = 0.5;
	}

	// fragment construtor
	StorageEffect(Element type, Point pt, Velocity v, double dx, double dy, double age, double size)
	{
		this->type = type;
		this->v.setDx(v.getDx() * 0.5 + dx);
		this->v.setDy(v.getDy() * 0.5 + dy);
		this->age = age;
		this->size = size;
		
	}
	Point getPoint() { return pt; }
	double getAge() { return age; }
	double getSize() { return size; }
	Velocity getV() { return v; }
	Point getPtEnd() { return ptEnd; }
	Element getType() { return type; }

	void setAge(double value) { age = value; }
	void setSize(double value) { size = value; }
};

class UserInputStorage
{

};
