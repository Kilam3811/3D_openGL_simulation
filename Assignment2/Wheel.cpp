#include "Wheel.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#define PI 3.14159265359
static double total_distance = 0;
Wheel::Wheel(double x_cor, double y_cor, double z_cor, double speed, double time, double radius,double depth,double rotation)
{
	x = x_cor;
	y = y_cor;
	z = z_cor;
	t = time;
	r = radius;
	v = speed;
	h = depth;


	double instant_distance = v*t;


	total_distance += instant_distance;
	double theta = total_distance / r;

	theta *= 180 / PI;
	angle = theta;
}

void Wheel::draw()
{
	setPosition(x, y, z);
	setRotation(0);
	setColor(1, 0.51, 0.4);
	positionInGL();
	setColorInGL();
	//Set up cylinder variable
	GLUquadric* cylinder = gluNewQuadric();
	//Move to the plane(Spcific position at first)
	glTranslated(0, r, -h / 2);
	//Call the function to draw out the cylinder
	gluCylinder(cylinder, r, r, h/1.5,100, 10);

	glPushMatrix();
	Rectangular rec(1.9 * r, 0.15 * 2 * r, h/1.5);
	rec.setColor(0.10, 0.10, 0.4);
	rec.setRotation(angle);
	rec.draw_rolling();
	glPopMatrix();
	
}
