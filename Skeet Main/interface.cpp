#pragma once
#include "point.h"
#include "effect.h"
#include "interface.h"
#include <list>
#include <cassert>

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

void Interface::drawLevel()
{
    // output the background
    drawBackground(time.level() * .1, 0.0, 0.0);

    // output the gun
    gun.display();

    // output the birds, bullets, and fragments
    for (auto effect : effects)
        effect->render();
    for (auto bullet : bullets)
        bullet->output();
    for (auto element : birds)
        element->draw();

    // status
    drawText(Point(10, dimensions.getY() - 30), score.getText());
    drawText(Point(dimensions.getX() / 2 - 30, dimensions.getY() - 30), time.getText());
    drawText(Point(dimensions.getX() - 110, dimensions.getY() - 30), hitRatio.getText());
}