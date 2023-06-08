#pragma once
#include "storage.h"
class Logic
{
private:
	Storage storage;
public:
	Logic();
	void advance();
	void spawn();
	void input();
	iterator begin();
	iterator end();
	int getFramesLeft();
	int getLevelNumber();
	double getGunAngle();
	bool isPlaying();
	bool isGameOver();
	double getPercentLeft();
};

