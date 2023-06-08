#pragma once
#include "storageElement.h"
#include "iterator.h"
#include <vector>
#include <array>
#include <assert.h>

#define FRAMES_PER_SECOND 30

using namespace std;

class Storage
{
private:
	vector<StorageElement> elements;
	int numBirds;
	int points;
	int numKilled;
	StorageTime time;
	StorageGun gun;
public:
	Storage();
	int getPoints() { return points; }
	int getNumKilled() { return numKilled; }
	int getNumMissed() { return numBirds - numKilled; }
	Iterator begin();
	Iterator end();
	IteratorBird beginBird();
	IteratorBird endBird();
	IteratorBullet beginBullet();
	IteratorBullet endBullet();
	void add(StorageElement* element);
	void reset();


};

class StorageTime
{
private:
	int framesLeft;
	int levelNumber;
	// length in seconds of each level
	array<int, 5> levelLength;
	// seconds from frames
	int secondsFromFrames(int frame) const
	{
		return frame / FRAMES_PER_SECOND;
	}
	// how long have we been in the level in seconds?
	int secondsInLevel() const
	{
		assert(levelNumber < (int)levelLength.size());
		return levelLength[levelNumber] - secondsFromFrames(framesLeft);
	}
};

class StorageGun
{
private:
	double angle;
	Point pt;
};
