#pragma once

class InterfaceElement
{
public:
	virtual void draw(StorageBird* element);
	virtual void draw(StorageBullet* element);
	virtual void draw(StorageEffect* element);
};

class InterfacePellet : public InterfaceElement
{
public:
	void draw(StorageBullet* element) override;
};

class InterfaceShrapnel: public InterfaceElement
{
public:
	void draw(StorageBullet* element) override;
};

class InterfaceBomb : public InterfaceElement
{
public:
	void draw(StorageBullet* element) override;
};

class InterfaceMissle : public InterfaceElement
{
public:
	void draw(StorageBullet* element) override;
};

class InterfaceStandard : public InterfaceElement
{
public:
	void draw(StorageBird* element) override;
};

class InterfaceFloater : public InterfaceElement
{
public:
	void draw(StorageBird* element) override;
};

class InterfaceCrazy : public InterfaceElement
{
public:
	void draw(StorageBird* element) override;
};

class InterfaceSinker : public InterfaceElement
{
public:
	void draw(StorageBird* element) override;
};

class InterfaceFragment : public InterfaceElement
{
public:
	void draw(StorageEffect* element) override;
};

class InterfaceStreek : public InterfaceElement
{
public:
	void draw(StorageEffect* element) override;
};

class InterfaceExhuast : public InterfaceElement
{
public:
	void draw(StorageEffect* element) override;
};

