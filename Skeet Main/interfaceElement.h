#pragma once

class InterfaceElement
{
public:
	void virtual draw() = 0;
};

class InterfacePellet : InterfaceElement
{
public:
	void draw() override;
};

class InterfaceShrapnel: InterfaceElement
{
public:
	void draw() override;
};

class InterfaceBomb : InterfaceElement
{
public:
	void draw() override;
};

class InterfaceMissle : InterfaceElement
{
public:
	void draw() override;
};

class InterfaceStandard : InterfaceElement
{
public:
	void draw() override;
};

class InterfaceFloater : InterfaceElement
{
public:
	void draw() override;
};

class InterfaceCrazy : InterfaceElement
{
public:
	void draw() override;
};

class InterfaceSinker : InterfaceElement
{
public:
	void draw() override;
};

class InterfaceFragment : InterfaceElement
{
public:
	void draw() override;
};

class InterfaceStreek : InterfaceElement
{
public:
	void draw() override;
};

class InterfaceExhuast : InterfaceElement
{
public:
	void draw() override;
};

