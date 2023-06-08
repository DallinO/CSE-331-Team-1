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


void InterfaceBird::drawDot(const Point& point, double radius = 2.0, double red = 1.0, double green = 1.0, double blue = 1.0) const
{
	// Get ready, get set...
	glBegin(GL_TRIANGLE_FAN);
	glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
	double r = radius / 2.0;

	// Go...
	glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() - r));
	glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() - r));
	glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() + r));
	glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() + r));

	// Done!  OK, that was a bit too dramatic
	glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
	glEnd();
}

void InterfaceBullet::drawLine(const Point& begin, const Point& end,
	double red, double green, double blue) const
{
	// Get ready...
	glBegin(GL_LINES);
	glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

	// Draw the actual line
	glVertexPoint(begin);
	glVertexPoint(end);

	// Complete drawing
	glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
	glEnd();
}

void InterfacePellet::draw(StorageElement* element)
{
	if (!element->isDead())
		drawDot(element->getPoint(), 3.0, 1.0, 1.0, 0.0);
}