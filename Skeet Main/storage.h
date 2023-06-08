#pragma once
#include "storageElement.h"
#include "iterator.h"
#include <vector>
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

};

class StorageGun
{

};
