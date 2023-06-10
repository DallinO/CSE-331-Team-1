#pragma once
#include "logicElement.h"

class InterfaceElement
{
public:
	virtual void draw() = 0;
};

class InterfacePellet : public InterfaceElement
{
public:
	void draw(BulletStorage* element);
};

class InterfaceShrapnel: public InterfaceElement
{
public:
	void draw(BulletStorage* element);
};

class InterfaceBomb : public InterfaceElement
{
public:
	void draw(BulletStorage* element);
};

class InterfaceMissle : public InterfaceElement
{
public:
	void draw(BulletStorage* element);
};

class InterfaceStandard : public InterfaceElement
{
public:
	void draw(StorageElement* element);
};

class InterfaceFloater : public InterfaceElement
{
public:
	void draw(StorageElement* element);
};

class InterfaceCrazy : public InterfaceElement
{
public:
	void draw(StorageElement* element);
};

class InterfaceSinker : public InterfaceElement
{
public:
	void draw(StorageElement* element);
};

class InterfaceFragment : public InterfaceElement
{
public:
	void draw(StorageEffect* element);
};

class InterfaceStreek : public InterfaceElement
{
public:
	void draw(StorageEffect* element);
};

class InterfaceExhuast : public InterfaceElement
{
public:
	void draw(StorageEffect* element);
};

class TimeInterface
{
public:
	string getText(Logic* logic) const
	{
		ostringstream sout;
		sout << "Time:  " << secondsLeft();
		return sout.str();
	}
};

class GunInterface
{
public:
	void display(GunLogic* gun) const;
};
