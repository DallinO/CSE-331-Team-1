#pragma once
#include "logic.h"

class Interface
{
private:
	Logic logic;
public:
	Interface();
	void input();
	void processing();
	void output();
};