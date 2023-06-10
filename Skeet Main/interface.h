#pragma once
#include "logic.h"
#include "uiInteract.h"
#include "interfaceElement.h"

class Interface
{
private:
	Logic logic;
	GunInterface gunInterface;
	InterfacePellet interfacePellet;
	InterfaceShrapnel interfaceShrapnel;
	InterfaceBomb interfaceBomb;
	InterfaceMissle interfaceMissle;
	InterfaceStandard interfaceStandard;
	InterfaceFloater interfaceFloater;
	InterfaceCrazy interfaceCrazy;
	InterfaceSinker interfaceSinker;
	InterfaceFragment interfaceFragment;
	InterfaceStreek interfaceStreek;
	InterfaceExhuast interfaceExuast;
	TimeInterface timeInterface;
	UserInput ui;

	void drawLevel();
	void drawStatus();
	void drawBackground(double redBack, double greenBack, double blueBack) const;

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