#include "logicElement.h"

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

bool BulletLogic::isOutOfBounds(BulletStorage* bullet) const
{
	return (bullet->getPoint().getX() < -bullet->getRadius() || bullet->getPoint().getX() >= bullet->getDimensions().getX() + bullet->getRadius() ||
		bullet->getPoint().getY() < -bullet->getRadius() || bullet->getPoint().getY() >= bullet->getDimensions().getY() + bullet->getRadius());
}

void BulletLogic::move(BulletStorage* bullet, list<StorageEffect*> effects)
{
	// inertia
	bullet->getPoint().add(bullet->getVelocity());

	// out of bounds checker
	if (isOutOfBounds(bullet))
		kill(bullet);
}



void BombLogic::move(BulletStorage* bullet, list<StorageEffect*> effects)
{
	// kill if it has been around too long
	bullet->setTimeToDie(bullet->getTimeToDie() - 1);
	if (!bullet->getTimeToDie())
		kill(bullet);

	// do the inertia thing
	BulletLogic::move(bullet, effects);
}