#include "logicElement.h"
#include "logic.h"
#include "enums.h"
#include <assert.h>

#define SECONDS_STATUS 5.0

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32

double random(double min, double max)
{
	assert(min <= max);
	double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
	assert(min <= num && num <= max);
	return num;
}

int randomInt(int min, int max)
{
	assert(min < max);
	int num = (rand() % (max - min)) + min;
	assert(min <= num && num <= max);
	return num;
}

double randomFloat(double min, double max)
{
	assert(min <= max);
	double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
	assert(min <= num && num <= max);
	return num;
}

bool BulletLogic::isOutOfBounds(BulletStorage* bullet) const
{
	return (bullet->getPoint().getX() < -bullet->getRadius() || bullet->getPoint().getX() >= bullet->getDimensions().getX() + bullet->getRadius() ||
		bullet->getPoint().getY() < -bullet->getRadius() || bullet->getPoint().getY() >= bullet->getDimensions().getY() + bullet->getRadius());
}

void BulletLogic::move(BulletStorage* bullet, list<StorageEffect>* effects)
{
	// inertia
	bullet->getPoint().add(bullet->getVelocity());

	// out of bounds checker
	if (isOutOfBounds(bullet))
		kill(bullet);
}



void BombLogic::move(BulletStorage* bullet, list<StorageEffect>* effects)
{
	// kill if it has been around too long
	bullet->setTimeToDie(bullet->getTimeToDie() - 1);
	if (!bullet->getTimeToDie())
		kill(bullet);

	// do the inertia thing
	BulletLogic::move(bullet, effects);
}

void BombLogic::death(BulletStorage* bullet, list<BulletStorage>* bullets)
{
	for (int i = 0; i < 20; i++)
		bullets->push_back(BulletStorage(*bullet));
}

void ShrapnelLogic::move(BulletStorage* bullet, list<StorageEffect>* effects)
{
	// kill if it has been around too long
	bullet->setTimeToDie(bullet->getTimeToDie() - 1);
	if (!bullet->getTimeToDie())
		kill(bullet);

	// add a streek
	effects->push_back(StorageEffect(Streek, bullet->getPoint(), bullet->getVelocity()));

	// do the usual bullet stuff (like inertia)
	BulletLogic::move(bullet, effects);
}

void MissleLogic::move(BulletStorage* bullet, list<StorageEffect>* effects)
{
	// add a streek
	effects->push_back(StorageEffect(Exaust, bullet->getPoint(), bullet->getVelocity(), random(-6.0, 6.0), random(-6.0, 6.0), random(0.4, 1.0), random(1.0, 2.5)));

	// do the usual bullet stuff (like inertia)
	BulletLogic::move(bullet, effects);
}

void FragmentLogic::fly(StorageEffect* effect)
{
	// move it forward with inertia (no gravity)
	effect->getPoint() += effect->getV();

	// increase the age so it fades away
	effect->setAge(effect->getAge() - 0.02);
	effect->setSize(effect->getSize() * 0.95);
}

void StreekLogic::fly(StorageEffect* effect)
{
	// move it forward with inertia (no gravity)
	effect->getPoint() += effect->getV();

	// increase the age so it fades away
	effect->setAge(effect->getAge() - 0.1);
}

void ExhaustLogic::fly(StorageEffect* effect)
{
	// move it forward with inertia (no gravity)
	effect->getPoint() += effect->getV();

	// increase the age so it fades away
	effect->setAge(effect->getAge() - 0.025);
}

bool BirdLogic::isOutOfBounds(BirdStorage* bird) const
{
	return (bird->getPoint().getX() < -bird->getRadius() || bird->getPoint().getX() >= bird->getDimensions().getX() + bird->getRadius() ||
		bird->getPoint().getY() < -bird->getRadius() || bird->getPoint().getY() >= bird->getDimensions().getY() + bird->getRadius());
}

void StandardLogic::advance(BirdStorage* bird)
{
	// small amount of drag
	bird->setVelocity( bird->getVelocity() *  0.995);

	// inertia
	bird->getPoint().add(bird->getVelocity());

	// out of bounds checker
	if (isOutOfBounds(bird))
	{
		bird->kill();
		bird->setPoints(bird->getPoints() * -1); // points go negative when it is missed!
	}
}

void FloaterLogic::advance(BirdStorage* bird)
{
	// large amount of drag
	bird->setVelocity(bird->getVelocity() * 0.990);

	// inertia
	bird->getPoint().add(bird->getVelocity());

	// anti-gravity
	bird->getVelocity().addDy(0.05);

	// out of bounds checker
	if (isOutOfBounds(bird))
	{
		bird->kill();
		bird->setPoints(bird->getPoints() * -1); // points go negative when it is missed!
	}
}

void CrazyLogic::advance(BirdStorage* bird)
{
	// erratic turns eery half a second or so
	if (randomInt(0, 15) == 0)
	{
		bird->getVelocity().addDy(randomFloat(-1.5, 1.5));
		bird->getVelocity().addDx(randomFloat(-1.5, 1.5));
	}

	// inertia
	bird->getPoint().add(bird->getVelocity());

	// out of bounds checker
	if (isOutOfBounds(bird))
	{
		bird->kill();
		bird->setPoints(bird->getPoints() * -1); // points go negative when it is missed!
	}
}

void SinkerLogic::advance(BirdStorage* bird)
{
	// gravity
	bird->getVelocity().addDy(-0.07);

	// inertia
	bird->getPoint().add(bird->getVelocity());

	// out of bounds checker
	if (isOutOfBounds(bird))
	{
		bird->kill();
		bird->setPoints(bird->getPoints() * -1); // points go negative when it is missed!
	}
}

void TimeLogic::reset(TimeStorage* time)
{
	// first level is 30 seconds in length, the first 5 are the status time
	time->setLevelLength({0, 30, 30, 45, 45});
	time->setLevelNumber(1);
	time->setFramesLeft(FRAMES_PER_SECOND * time->getLevelLength()[time->getLevelNumber()]);
}

/************************
 * TIME IS PLAYING
 * Are we currently in a game playing time?
 ************************/
bool TimeLogic::isPlaying(TimeStorage* time) const
{
	// the first 5 seconds are not game plahing time.
	return secondsInLevel(time) > SECONDS_STATUS;
}

/************************
 * TIME PERCENT LEFT
 * What percent is left?
 ************************/
double TimeLogic::percentLeft(TimeStorage* time) const
{
	assert(time->getLevelNumber() >= 0 && time->getLevelNumber() < (int)time->getLevelLength().size());
	double framesInStatus = SECONDS_STATUS * FRAMES_PER_SECOND;
	double framesInPlaying = (time->getLevelLength()[time->getLevelNumber()] - SECONDS_STATUS) * FRAMES_PER_SECOND;

	if (isStatus(time))
	{
		assert(time->getFramesLeft() - framesInPlaying <= framesInStatus);
		assert(time->getFramesLeft() - framesInPlaying >= 0);
		assert(framesInStatus > 0);
		return (double)(time->getFramesLeft() - framesInPlaying) / (double)framesInStatus;
	}
	else
	{
		assert(time->getFramesLeft() - framesInStatus <= framesInPlaying);
		assert(time->getFramesLeft() - framesInStatus >= 0);
		assert(framesInPlaying > 0);
		return (double)(time->getFramesLeft() - framesInStatus) / (double)framesInPlaying;
	}
}

/************************
 * TIME SECONDS LEFT
 * How much time left, including status messages
 ************************/
int TimeLogic::secondsLeft(TimeStorage* time) const
{
	assert(time->getLevelNumber() >= 0 && time->getLevelNumber() < (int)time->getLevelLength().size());
	if (isStatus(time))
		return secondsFromFrames(time->getFramesLeft()) - time->getLevelLength()[time->getLevelNumber()] + (int)SECONDS_STATUS + 1;
	else
		return secondsFromFrames(time->getFramesLeft()) + 1;
}

/************************
 * TIME IS START LEVEL
 * Os this the very start of the playing time of the leve
 ************************/
bool TimeLogic::isStartLevel(TimeStorage* time) const
{
	if (isPlaying(time))
		return time->getFramesLeft() == FRAMES_PER_SECOND * (time->getLevelLength()[time->getLevelNumber()] - (int)SECONDS_STATUS) - 1;
	else
		return false;
}

void GunLogic::interact(GunStorage* gun, int clockwise, int counterclockwise)
{
	// move it
	if (clockwise > 0)
	{
		gun->setAngle( gun->getAngle() + (clockwise > 10) ? 0.06 : 0.025);
		if (gun->getAngle() > M_PI_2)
			gun->setAngle(M_PI_2);
	}
	if (counterclockwise > 0)
	{
		gun->setAngle(gun->getAngle() - (clockwise > 10) ? 0.06 : 0.025);
		if (gun->getAngle() > 0.0)
			gun->setAngle(0.0);
	}
}