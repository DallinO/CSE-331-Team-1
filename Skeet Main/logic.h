#pragma once
#include "storage.h"
#include "iterator.h"
#include "logicElement.h"
#include "uiInteract.h"
class Logic
{
private:
	Storage storage;
	StandardLogic standardlogic;
	FloaterLogic floaterLogic;
	CrazyLogic crazyLogic;
	SinkerLogic sinkerLogic;
	BombLogic bombLogic;
	ShrapnelLogic shrapnelLogic;
	MissleLogic missleLogic;
	EffectLogic effectLogic;
	FragmentLogic fragmentLogic;
	StreekLogic streekLogic;
	ExhaustLogic exhaustLogic;
	TimeLogic timeLogic;
	GunLogic gunLogic;

	void spawn(Storage* storage, TimeStorage* time, list<BirdStorage>* birds);
	void advance(Storage* storage, list<BirdStorage>* birds, list<BulletStorage>* bullets, list<StorageEffect>* effects);
	void hitDetection(HitRatio* hitRatio, list<BirdStorage>* birds, list<BulletStorage>* bullets, list<StorageEffect>* effects);
	void cleanUp(Score* score, list<BirdStorage>* birds, list<BulletStorage>* bullets, list<StorageEffect>* effects);

public:
	Logic();
	void animate();
	void interact(const UserInput& ui);
	bool isPlaying() { return timeLogic.isPlaying(storage.getTime()); }


	
	
	void input();
	Iterator begin();
	Iterator end();
	int getFramesLeft();
	int getLevelNumber();
	double getGunAngle();
	bool isPlaying();
	bool isGameOver();
	double getPercentLeft();

	Storage* getStorage() { return &storage; }
	StandardLogic getStandardLogic(){return standardlogic;}
	FloaterLogic getFloaterLogic() { return floaterLogic; }
	CrazyLogic getCrazyLogic() { return crazyLogic; }
	SinkerLogic getSinkerLogic() { return sinkerLogic; }
	BombLogic getBombLogic() { return bombLogic; }
	ShrapnelLogic getShrapnelLogic() { return shrapnelLogic; }
	MissleLogic getMissleLogic() { return missleLogic; }
	FragmentLogic getFragmentLogic() { return fragmentLogic; }
	StreekLogic getStreekLogic() { return streekLogic; }
	ExhaustLogic getExhaustLogic() { return exhaustLogic; }
	TimeLogic getTimeLogic() { return timeLogic; }
	GunLogic getGunLogic() { return gunLogic; }
};

