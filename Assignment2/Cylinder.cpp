#include "Cylinder.h"
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
Cylinder::Cylinder(double radius_, double depth_, double slices_, double stacks_)
{
	set_Dimension(radius_, depth_, slices_, stacks_);
}
void Cylinder::draw()
{
	//Adjust the position of the cylinder.
	positionInGL();
	setColorInGL();

	//Set up cylinder variable
	GLUquadric* cylinder = gluNewQuadric();
	//Move to the plane(Spcific position at first)
	glTranslated(0,getRadius(),-getHeight()/2);
	//Call the function to draw out the cylinder
	gluCylinder(cylinder,getRadius(),getRadius(),getHeight(),getSlices(),getStacks());

	//Draw the disk to cover top and bottom side(circles)
	gluDisk(cylinder,0,getRadius(),getSlices(),10);
	glTranslated(0, 0, getHeight());
	gluDisk(cylinder, 0, getRadius(), getSlices(), 10);

}

void Cylinder::Rolling()
{
	//Move to the centre of the wheel and rotate about -z axis
	glTranslated(x, y, z);
	glRotated(rotation, 0, 0, -1);
	glTranslated(0, 0, 0);

}

void Cylinder::draw_rolling()
{
	//Rolling each time..
	Rolling();
	setColorInGL();


	//Set up cylinder variable
	GLUquadric* cylinder = gluNewQuadric();
	//Move to the plane(Spcific position at first)
	glTranslated(0, getRadius(),-getHeight()/2);
	//Call the function to draw out the cylinder
	gluCylinder(cylinder, getRadius(), getRadius(), getHeight(), getSlices(), getStacks());
	//Draw the disk to cover top and bottom side(circles)
	gluDisk(cylinder, 0, getRadius(), getSlices(), 10);
	glTranslated(0, 0, getHeight());
	gluDisk(cylinder, 0, getRadius(), getSlices(), 10);
}

void Cylinder::set_Dimension(double radius_, double depth_, double slices_, double stacks_)
{
	radius = radius_;
	depth = depth_ ;
	slices = slices_;
	stacks = stacks_;
}



double Cylinder::getRadius()
{
	return radius;
}

double Cylinder::getHeight()
{
	return depth;
}

double Cylinder::getSlices()
{
	return slices;
}

double Cylinder::getStacks()
{
	return stacks;
}
