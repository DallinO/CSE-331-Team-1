#pragma once
#include "point.h"
#include "effect.h"
#include "interface.h"
#include "enums.h"
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

void drawText(const Point& topLeft, const char* text)
{
    void* pFont = GLUT_TEXT;
    glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);

    // prepare to output the text from the top-left corner
    glRasterPos2f((GLfloat)topLeft.getX(), (GLfloat)topLeft.getY());

    // loop through the text
    for (const char* p = text; *p; p++)
        glutBitmapCharacter(pFont, *p);
}

void drawText(const Point& topLeft, const string& text)
{
    drawText(topLeft, text.c_str());
}

void Interface::drawBackground(double redBack, double greenBack, double blueBack, Point dimensions) const
{
    glBegin(GL_TRIANGLE_FAN);

    // two rectangles is the fastest way to fill the screen.
    glColor3f((GLfloat)redBack /* red % */, (GLfloat)greenBack /* green % */, (GLfloat)blueBack /* blue % */);
    glVertex2f((GLfloat)0.0, (GLfloat)0.0);
    glVertex2f((GLfloat)dimensions.getX(), (GLfloat)0.0);
    glVertex2f((GLfloat)dimensions.getX(), (GLfloat)dimensions.getY());
    glVertex2f((GLfloat)0.0, (GLfloat)dimensions.getY());

    glEnd();
}

void Interface::drawLevel()
{
    Storage* storage = logic.getStorage();
    GunStorage* gun = storage->getGun();
    TimeStorage* time = storage->getTime();
    list<BulletStorage>* bullets = storage->getBullets();
    list<BirdStorage>* birds = storage->getBirds();
    list<StorageEffect>* effects = storage->getEffects();
    Point dimensions = storage->getDimensions();
    Score* score = storage->getScore();
    HitRatio* hitRatio = storage->getHitRatio();
    // output the background
    drawBackground(logic.getStorage()->getTime()->getLevelNumber() * .1, 0.0, 0.0, dimensions);

    // output the gun
    gunInterface.display(gun);

    // output the birds, bullets, and fragments
    for (auto& effect : *effects)
    {
        switch (effect.getType())
        {
            case Fragment:
                interfaceFragment.draw(&effect);
                break;
            case Streek:
                interfaceStreek.draw(&effect);
                break;
            case Exaust:
                interfaceExuast.draw(&effect);
                break;
        }
    }
    for (auto& bullet : *bullets)
    {
        switch (bullet.getType())
        {
            case Pellet:
                interfaceStandard.draw(&bullet);
                break;
            case Bomb:
                interfaceSinker.draw(&bullet);
                break;
            case Shrapnel:
                interfaceFloater.draw(&bullet);
                break;
            case Missle:
                interfaceCrazy.draw(&bullet);
                break;
        }
    }
    for (auto& bird : *birds)
    {
        switch (bird.getType())
        {
        case Standard:
            interfaceStandard.draw(&bird);
            break;
        case Sinker:
            interfaceSinker.draw(&bird);
            break;
        case Floater:
            interfaceFloater.draw(&bird);
            break;
        case Crazy:
            interfaceCrazy.draw(&bird);
            break;
        }
    }

    // status
    drawText(Point(10, dimensions.getY() - 30), score->getText());
    drawText(Point(dimensions.getX() / 2 - 30, dimensions.getY() - 30), timeInterface.getText(&logic, storage));
    drawText(Point(dimensions.getX() - 110, dimensions.getY() - 30), hitRatio->getText());
}

void Interface::drawTimer(double percent,
    double redFore, double greenFore, double blueFore,
    double redBack, double greenBack, double blueBack) const
{
    double radians;
    Storage* storage = logic.getStorage();
    Point dimensions = storage->getDimensions();

    GLfloat length = (GLfloat)dimensions.getX();
    GLfloat half = length / (GLfloat)2.0;

    // do the background stuff
    drawBackground(redBack, greenBack, blueBack, dimensions);

    // foreground stuff
    radians = percent * M_PI * 2.0;
    GLfloat x_extent = half + length * (GLfloat)sin(radians);
    GLfloat y_extent = half + length * (GLfloat)cos(radians);

    // get read to draw the triangles
    glBegin(GL_TRIANGLE_FAN);
    glColor3f((GLfloat)redFore /* red % */, (GLfloat)greenFore /* green % */, (GLfloat)blueFore /* blue % */);
    glVertex2f(half, half);

    // fill in the triangles, one eight at a time
    switch ((int)(percent * 8.0))
    {
    case 7: // 315 - 360
        glVertex2f(half, length);
        glVertex2f(length, length);
        glVertex2f(length, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, length);
        break;
    case 6: // 270 - 315
        glVertex2f(half, length);
        glVertex2f(length, length);
        glVertex2f(length, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, half);
        break;
    case 5: // 225 - 270
        glVertex2f(half, length);
        glVertex2f(length, length);
        glVertex2f(length, 0.0);
        glVertex2f(0.0, 0.0);
        break;
    case 4: // 180 - 225
        glVertex2f(half, length);
        glVertex2f(length, length);
        glVertex2f(length, 0.0);
        glVertex2f(half, 0.0);
        break;
    case 3: // 135 - 180
        glVertex2f(half, length);
        glVertex2f(length, length);
        glVertex2f(length, half);
        glVertex2f(length, 0.0);
        break;
    case 2: // 90 - 135 degrees
        glVertex2f(half, length);
        glVertex2f(length, length);
        glVertex2f(length, half);
        break;
    case 1: // 45 - 90 degrees
        glVertex2f(half, length);
        glVertex2f(length, length);
        break;
    case 0: // 0 - 45 degrees
        glVertex2f(half, length);
        break;
    }
    glVertex2f(x_extent, y_extent);

    // complete drawing
    glEnd();

    // draw the red line now
    glBegin(GL_LINES);
    glColor3f((GLfloat)0.6, (GLfloat)0.0, (GLfloat)0.0);
    glVertex2f(half, half);
    glVertex2f(x_extent, y_extent);
    glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
    glEnd();
}

void Interface::drawStatus()
{
    ostringstream sout;
    Storage* storage = logic.getStorage();
    GunStorage* gun = storage->getGun();
    TimeStorage* time = storage->getTime();
    list<BulletStorage>* bullets = storage->getBullets();
    list<BirdStorage>* birds = storage->getBirds();
    list<StorageEffect>* effects = storage->getEffects();
    Point dimensions = storage->getDimensions();
    Score* score = storage->getScore();
    HitRatio* hitRatio = storage->getHitRatio();

    if (logic.getTimeLogic().isGameOver(time))
    {
        // draw the end of game message
        drawText(Point(dimensions.getX() / 2 - 30, dimensions.getY() / 2 + 10),
            "Game Over");

        // draw end of game status
        drawText(Point(dimensions.getX() / 2 - 30, dimensions.getY() / 2 - 10),
            score->getText());
    }
    else
    {
        // output the status timer
        drawTimer(1.0 - logic.getTimeLogic().percentLeft(time),
            (time->getLevelNumber() - 0.0) * .1, 0.0, 0.0,
            (time->getLevelNumber() - 1.0) * .1, 0.0, 0.0);

        // draw the message giving a countdown
        sout << "Level " << time->getLevelNumber()
            << " begins in " << logic.getTimeLogic().secondsLeft(time) << " seconds";
        drawText(Point(dimensions.getX() / 2 - 110, dimensions.getY() / 2 - 10),
            sout.str());
    }
}