#pragma once
#include "storage.h"
#include "iterator.h"
class Logic
{
private:
	Storage storage;
public:
	Logic();
	void advance();
	void spawn();
	void input();
	Iterator begin();
	Iterator end();
	int getFramesLeft();
	int getLevelNumber();
	double getGunAngle();
	bool isPlaying();
	bool isGameOver();
	double getPercentLeft();
};

