#pragma once

class InterfaceElement
{
public:
	void virtual draw() = 0;
};

class InterfacePellet : InterfaceElement
{
public:
	void draw();
};

class InterfaceShrapnel: InterfaceElement
{
public:
	void draw();
};

class InterfaceBomb : InterfaceElement
{
public:
	void draw();
};

class InterfaceMissle : InterfaceElement
{
public:
	void draw();
};

class InterfaceStandard : InterfaceElement
{
public:
	void draw();
};

class InterfaceFloater : InterfaceElement
{
public:
	void draw();
};

class InterfaceCrazy : InterfaceElement
{
public:
	void draw();
};

class InterfaceSinker : InterfaceElement
{
public:
	void draw();
};

class InterfaceFragment : InterfaceElement
{
public:
	void draw();
};

class InterfaceStreek : InterfaceElement
{
public:
	void draw();
};

class InterfaceExhuast : InterfaceElement
{
public:
	void draw();
};

