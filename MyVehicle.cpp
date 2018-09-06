#include "MyVehicle.h"
#include "Triangular.h"
#include "Rectangular.h"
#include "Cylinder.h"
#include "Trapezoidal.h"
#include "VectorMaths.hpp"
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
MyVehicle::MyVehicle() {};
MyVehicle::~MyVehicle() {};
void MyVehicle::draw()
{
	//SAMPLE CAR



	// move to the vehicle¡¦s local frame of reference
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(-rotation, 0, 1, 0);
	// all the local drawing code

	//Body
	Rectangular rec1;
	rec1.setLength(3, 1, 2);
	rec1.setPosition(0, 0.4, 0);
	rec1.positionInGL();
	rec1.setColor(255, 186, 221);
	rec1.setColorInGL();
	rec1.draw();
	//glPopMatrix();

	//glPushMatrix();

	//front right(seen from initial position)
	Cylinder cy1;
	cy1.set_Dimension(0.4, 0.1, 100, 10);
	cy1.setColor(145,207,255);
	cy1.setPosition(1.1, -0.4, 1.1);
	cy1.positionInGL();
	cy1.setColorInGL();
	cy1.draw();
	//glPopMatrix();

	//front left(seen from initial position)
	//glPushMatrix();
	Cylinder cy2;
	cy2.set_Dimension(0.4, 0.1, 100, 10);
	cy2.setColor(145,207,255);
	cy2.setPosition(0, 0, -2.2);
	cy2.positionInGL();
	cy2.setColorInGL();
	cy2.draw();
	//glPopMatrix();

	//back right(seen from initial position)
	//glPushMatrix();
	Cylinder cy3;
	cy3.set_Dimension(0.8, 0.1, 100, 10);
	cy3.setColor(255, 224, 147);
	cy3.setPosition(-2.2, 0, 0);
	cy3.positionInGL();
	cy3.setColorInGL();
	cy3.draw();
	//glPopMatrix();

	//back left(seen from initial position)
	//glPushMatrix();
	Cylinder cy4;
	cy4.set_Dimension(0.8, 0.1, 100, 10);
	cy4.setColor(255, 224, 147);
	cy4.setPosition(0, 0, 2.2);
	cy4.positionInGL();
	cy4.setColorInGL();
	cy4.draw();
	glPopMatrix();



	/*glPushMatrix();
	Rectangular rec2;
	rec2.setLength(1.5, 0.05, 0.05);
	rec2.setColor(0, 201, 124);
	rec2.setPosition(0.5, 1.4, 0);
	rec2.positionInGL();
	rec2.setColorInGL();
	rec2.draw();
	glPopMatrix();

	glPushMatrix();
	Cylinder cy5;
	cy5.set_Dimension(0.15, 0.05, 100, 10);
	cy5.setColor(17, 57, 122);
	glRotated(90, -1, 0, 0);
	cy5.setPosition(-0.7, 10, 0.1);

	glTranslated(0, -10.15, 1.35);
	cy5.positionInGL();
	cy5.setColorInGL();
	cy5.draw();
	glPopMatrix();

	glPushMatrix();
	Cylinder cy6;
	cy6.set_Dimension(0.25, 0.05, 100, 10);
	cy6.setColor(255, 255, 255);
	cy6.setPosition(-0.7, 10, 0.1);
	glRotated(90, -1, 0, 0);
	glTranslated(0, -10.25, 1.30);
	cy6.positionInGL();
	cy6.setColorInGL();
	cy6.draw();

	glPopMatrix();

	glPushMatrix();
	Cylinder cy7;
	cy7.set_Dimension(0.35, 0.05, 100, 10);
	cy7.setColor(17, 57, 122);
	cy7.setPosition(-0.7, 10, 0.13);
	glRotated(90, -1, 0, 0);
	glTranslated(0, -10.35, 1.25);
	cy7.positionInGL();
	cy7.setColorInGL();
	cy7.draw();
	glPopMatrix();*/


	/*glPushMatrix();

	glBegin(GL_POLYGON);


	int z = 1;
	while (z < 10) {
	double theta = 0;
	do {
	x = (3 * sin(theta))*cos(3 * theta);
	y = (14 * sin(theta))*sin(6 * theta);
	glVertex3d(x, y, z);

	glColor3d(209 / 255.0, 244 / 255.0, 66.0 / 255);
	theta += 0.01;
	} while (theta < 2 * PI);

	z+=1;
	}
	glEnd();

	glPopMatrix();*/

	// move back to global frame of reference
	
	
}
