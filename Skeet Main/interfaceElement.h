#pragma once

class InterfaceElement
{
public:
	void virtual draw(StorageElement* element) = 0;
};

class InterfacePellet : public InterfaceElement
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

