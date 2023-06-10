#pragma once
#include "logic.h"
#include "uiInteract.h"

class Interface
{
private:
	Logic logic;
	UserInput ui;
public:
	Interface(const UserInput& ui) { this->ui = ui; }
	void run()
	{
		logic.interact(ui);
		logic.animate();
		if (logic.isPlaying())
			drawLevel();
		else
			drawStatus();
	}
	void drawLevel();
	void drawStatus();
};