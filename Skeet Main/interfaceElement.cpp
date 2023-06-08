#include "interfaceElement.h"
#include "interface.h"

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

inline void glVertexPoint(const Point& point)
{
	glVertex2f((GLfloat)point.getX(), (GLfloat)point.getY());
}

void drawDot(const Point& point, double radius = 2.0, double red = 1.0, double green = 1.0, double blue = 1.0)
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

void drawLine(const Point& begin, const Point& end,
	double red, double green, double blue)
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

void drawDisk(const Point& center, double radius,
	double red, double green, double blue)
{
	assert(radius > 1.0);
	const double increment = M_PI / radius;  // bigger the circle, the more increments

	// begin drawing
	glBegin(GL_TRIANGLES);
	glColor3f((GLfloat)red /* red % */, (GLfloat)green /* green % */, (GLfloat)blue /* blue % */);

	// three points: center, pt1, pt2
	Point pt1;
	pt1.setX(center.getX() + (radius * cos(0.0)));
	pt1.setY(center.getY() + (radius * sin(0.0)));
	Point pt2(pt1);

	// go around the circle
	for (double radians = increment;
		radians <= M_PI * 2.0 + .5;
		radians += increment)
	{
		pt2.setX(center.getX() + (radius * cos(radians)));
		pt2.setY(center.getY() + (radius * sin(radians)));

		glVertex2f((GLfloat)center.getX(), (GLfloat)center.getY());
		glVertex2f((GLfloat)pt1.getX(), (GLfloat)pt1.getY());
		glVertex2f((GLfloat)pt2.getX(), (GLfloat)pt2.getY());

		pt1 = pt2;
	}

	// complete drawing
	glEnd();
}

void InterfacePellet::draw(StorageElement* element)
{
	if (!element->isDead())
		drawDot(element->getPoint(), 3.0, 1.0, 1.0, 0.0);
}

void InterfaceShrapnel::draw(StorageElement* element)
{
	if (!element->isDead())
		drawDot(element->getPoint(), element->getRadius(), 1.0, 1.0, 0.0);
}

void InterfaceBomb::draw(StorageElement* element)
{
	if (!element->isDead())
	{
		// Bomb actually has a gradient to cut out the harsh edges
		drawDot(element->getPoint(), element->getRadius() + 2.0, 0.50, 0.50, 0.00);
		drawDot(element->getPoint(), element->getRadius() + 1.0, 0.75, 0.75, 0.00);
		drawDot(element->getPoint(), element->getRadius() + 0.0, 0.87, 0.87, 0.00);
		drawDot(element->getPoint(), element->getRadius() - 1.0, 1.00, 1.00, 0.00);
	}
}

void InterfaceMissle::draw(StorageElement* element)
{
	if (!element->isDead())
	{
		// missile is a line with a dot at the end so it looks like fins.
		Point ptNext(element->getPoint());
		ptNext.add(element->getVelocity());
		drawLine(element->getPoint(), ptNext, 1.0, 1.0, 0.0);
		drawDot(element->getPoint(), 3.0, 1.0, 1.0, 1.0);
	}
}
