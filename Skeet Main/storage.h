#pragma once
#include "storageElement.h"
#include "iterator.h"
#include "score.h"
#include <list>
#include <array>
#include <assert.h>

#define FRAMES_PER_SECOND 30
#define WIDTH  800.0
#define HEIGHT 800.0

using namespace std;

class Storage
{
private:
	list<BirdStorage> birds;
	list<BulletStorage> bullets;
	list<StorageEffect> effects;
	int numBirds;
	int points;
	int numKilled;
	TimeStorage time;
	GunStorage gun;
	HitRatio hitRatio;
	Score score;
	Point dimensions = Point(WIDTH, HEIGHT);

public:
	Storage();
	int* getPoints() { return &points; }
	int* getNumKilled() { return &numKilled; }
	int getNumMissed() { return numBirds - numKilled; }
	list<BirdStorage>* getBirds() { return &birds; }
	list<BulletStorage>* getBullets() { return &bullets; }
	list<StorageEffect>* getEffects() { return &effects; }
	TimeStorage* getTime() { return &time; }
	GunStorage* getGun() { return &gun; }
	HitRatio* getHitRatio() { return &hitRatio; }
	Score* getScore() { return &score; }
	Point getDimensions() { return dimensions; }
};

class GunStorage
{
private:
	Point pt;
	double angle;
public:
	GunStorage(const Point& pt) : angle(0.78 /* 45 degrees */), pt(pt) {}
	Point getPoint() { return pt; }
	double getAngle() { return angle; }

	void setPoint(Point pt) { this->pt = pt; }
	void setAngle(double angle) { this->angle = angle; }
};

class TimeStorage
{
private:
	int framesLeft;
	int levelNumber;
	array<int, 5> levelLength;

public:
	int getFramesLeft() { return framesLeft; }
	int getLevelNumber() { return levelNumber; }
	array<int, 5> getLevelLength() { return levelLength; }

	void setFramesLeft(int value) { framesLeft = value; }
	void setLevelNumber(int value) { levelNumber = value; }
	void setLevelLength(array<int, 5> array) { levelLength = array; }
	void operator++(int postfix)
	{
		assert(levelNumber >= 0 && levelNumber < (int)levelLength.size());

		// do nothing in the game over scenario
		if (levelNumber == 0)
			return;

		// standard move withing a level
		if (framesLeft >= 1)
			framesLeft--;

		// changing the level
		else
		{
			// move the level or...
			levelNumber++;
			if (levelNumber < (int)levelLength.size())
				framesLeft = FRAMES_PER_SECOND * levelLength[levelNumber];

			// game over!
			else
				levelNumber = 0;
		}
	}
};
