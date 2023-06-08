#pragma once
#include "storageElement.h"

class LogicElement
{
public:
	void virtual advance(StorageElement* storage);
	void virtual turn(StorageElement* storage);
};

class LogicPellet : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};

class LogicShrapnel : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};

class LogicBomb : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};

class LogicMissle : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};

class LogicStandard : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};

class LogicFloater : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};

class LogicCrazy : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};

class LogicSinker : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};

class LogicFragment : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};

class LogicStreek : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};

class LogicExhuast : LogicElement
{
public:
	void advance(StorageElement* storage) override;
	void turn(StorageElement* storage) override;
};