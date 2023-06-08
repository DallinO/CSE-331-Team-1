#pragma once
#include "storageElement.h"

class InterfaceElement
{
public:
	virtual void draw(StorageElement* element) = 0;
};

class InterfaceBullet : public InterfaceElement
{
protected:
	void drawLine(const Point& begin, const Point& end,
		double red = 1.0, double green = 1.0, double blue = 1.0) const;
	void drawDot(const Point& point, double radius = 2.0,
		double red = 1.0, double green = 1.0, double blue = 1.0) const;
	int random(int min, int max);
	double random(double min, double max);
};

class InterfacePellet : public InterfaceBird
{
public:
	void draw(StorageElement* element) override;
};

class InterfaceShrapnel: public InterfaceElement
{
public:
	void draw(StorageElement* element) override;
};

class InterfaceBomb : public InterfaceElement
{
public:
	void draw(StorageElement* element) override;
};

class InterfaceMissle : public InterfaceElement
{
public:
	void draw(StorageElement* element) override;
};

class InterfaceStandard : public InterfaceElement
{
public:
	void draw(StorageElement* element) override;
};

class InterfaceFloater : public InterfaceElement
{
public:
	void draw(StorageElement* element) override;
};

class InterfaceCrazy : public InterfaceElement
{
public:
	void draw(StorageElement* element) override;
};

class InterfaceSinker : public InterfaceElement
{
public:
	void draw(StorageElement* element) override;
};

class InterfaceFragment : public InterfaceElement
{
public:
	void draw(StorageElement* element) override;
};

class InterfaceStreek : public InterfaceElement
{
public:
	void draw(StorageElement* element) override;
};

class InterfaceExhuast : public InterfaceElement
{
public:
	void draw(StorageElement* element) override;
};

