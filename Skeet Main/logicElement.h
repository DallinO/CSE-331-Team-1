#pragma once
#include "storageElement.h"
#include <list>

#define FRAMES_PER_SECOND 30

class BirdLogic
{
protected:
	void virtual advance(BirdStorage* bird) {};
	void kill(BirdStorage* bird) { bird->kill(); }
	bool isOutOfBounds(BirdStorage* bird) const;
};

class StandardLogic : public BirdLogic
{
public:
	void advance(BirdStorage* bird);
};

class FloaterLogic : public BirdLogic
{
public:
	void advance(BirdStorage* bird);
};

class CrazyLogic : public BirdLogic
{
public:
	void advance(BirdStorage* bird);
};

class SinkerLogic : public BirdLogic
{
public:
	void advance(BirdStorage* bird);
};

class BulletLogic
{
protected:
	bool isOutOfBounds(BulletStorage* bullet) const;
	void kill(BulletStorage* bullet) { bullet->kill(); }
	void virtual death(BulletStorage* bullet, list<BulletStorage>* bullets) {}
	void virtual move(BulletStorage* bullet, list<StorageEffect>* effects);
	void input(BulletStorage* bullet, bool isUp, bool isDown, bool isB) {}
};

class BombLogic : public BulletLogic
{
public:
	void death(BulletStorage* bullet, list<BulletStorage>* bullets);
	void move(BulletStorage* bullet, list<StorageEffect>* effects);
};

class ShrapnelLogic : public BulletLogic
{
public:
	void move(BulletStorage* bullet, list<StorageEffect>* effects);
};

class MissleLogic : public BulletLogic
{
public:
	void move(BulletStorage* bullet, list<StorageEffect>* effects);
	void input(BulletStorage* bullet, bool isUp, bool isDown, bool isB)
	{
		if (isUp)
			bullet->getVelocity().turn(0.04);
		if (isDown)
			bullet->getVelocity().turn(-0.04);
	}
};

class EffectLogic
{
protected:
	void virtual fly(StorageEffect* effect) {}
public:
	bool isDead(StorageEffect* effect) { return effect->getAge() <= 0.0; }
};

class FragmentLogic : public EffectLogic
{
public:
	void fly(StorageEffect* effect);
};

class StreekLogic : public EffectLogic
{
public:
	void fly(StorageEffect* effect);
};

class ExhaustLogic : public EffectLogic
{
public:
	void fly(StorageEffect* effect);
};

class TimeLogic
{
private:
	int secondsFromFrames(int frame) const
	{
		return frame / FRAMES_PER_SECOND;
	}

	int secondsInLevel(TimeStorage* time) const
	{
		assert(time->getLevelNumber() < (int)time->getLevelLength().size());
		return time->getLevelLength()[time->getLevelNumber()] - secondsFromFrames(time->getFramesLeft());
	}

public:

	TimeLogic(TimeStorage* time) { reset(time); }
	// are we currently playing in a level?
	bool isPlaying(TimeStorage* time) const;
	// are we currently showing the status screen?
	bool isStatus(TimeStorage* time) const { return !isPlaying(time); }
	// has the game ended?
	bool isGameOver(TimeStorage* time) const { return time->getLevelNumber() == 0; }
	// is this the very start of the playing time of the leve
	bool isStartLevel(TimeStorage* time) const;
	// how much time is there left?
	int secondsLeft(TimeStorage* time) const;
	// what percent is left?
	double percentLeft(TimeStorage* time) const;
	// text
	string getText(TimeStorage* time) const;
	// reset
	void reset(TimeStorage* time);
};

class GunLogic
{
public:
	void interact(GunStorage* gun, int clockwise, int counterclockwise);
};