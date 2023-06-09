#pragma once
#include "StorageElement.h"
#include <list>

class BirdLogic
{
protected:
	void virtual advance(StorageElement* bird);
	void kill(StorageElement* bird);
	bool isOutOfBounds(StorageElement* element) const;
};

class StandardLogic : public BirdLogic
{
public:
	void advance(StorageElement* bird);
};

class FloaterLogic : public BirdLogic
{
public:
	void advance(StorageElement* bird);
};

class CrazyLogic : public BirdLogic
{
public:
	void advance(StorageElement* bird);
};

class SinkerLogic : public BirdLogic
{
public:
	void advance(StorageElement* bird);
};

class BulletLogic
{
protected:
	bool isOutOfBounds(BulletStorage* bullet) const;
	void kill(BulletStorage* bullet);
	void virtual death(BulletStorage* bullet, list<BulletStorage*> bullets);
	void virtual move(BulletStorage* bullet, list<StorageEffect*> effects);
};

class BombLogic : public BulletLogic
{
public:
	void death(BulletStorage* bullet, list<BulletStorage*> bullets);
	void move(BulletStorage* bullet, list<StorageEffect*> effects);
};

class ShrapnelLogic : public BulletLogic
{
public:
	void move(BulletStorage* bullet, list<StorageEffect*> effects);
};

class MissleLogic : public BulletLogic
{
public:
	void move(BulletStorage* bullet, list<StorageEffect*> effects);
};

class EffectLogic
{
protected:
	void virtual fly(StorageEffect* effect);
	bool isDead(StorageEffect* effect);
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

class ExhuasttLogic : public EffectLogic
{
public:
	void fly(StorageEffect* effect);
};