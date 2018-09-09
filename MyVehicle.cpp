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
MyVehicle::~MyVehicle() {}

void MyVehicle::for_spin()
{
	spin = spin + speed;
	
	while (spin > 360) {
		spin = spin - 360;
	}
	
	while (spin < 0) {
		spin = spin + 360;
	}
}
void MyVehicle::jud_spin(double X,double Y,double Z)
{
	if (speed >= 0) {
		for_spin();
		glTranslated(X, Y, Z);
		glRotated(-spin, 0, 0, 1);
		glTranslated(-X, -Y, -Z);
	}

	if (speed < 0) {
		for_spin();
		glTranslated(X, Y, Z);
		glRotated(-spin, 0, 0, 1);
		glTranslated(-X, -Y, -Z);
	}

}
;
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
	rec1.setColor(209, 110, 256);
	rec1.draw();
	//glPopMatrix();

	
	
	//front right(seen from initial position)
	glPushMatrix();
	Cylinder cy1;
	cy1.set_Dimension(0.4, 0.1, 100, 10);
	cy1.setColor(145,207,255);
	
	// Rotate follow the steering
	glTranslated(1.1, 0.4, 1.1);
	glRotated(-steering, 0, 1, 0);
	glTranslated(-1.1, -0.4, -1.1);

	// judge the spin
	jud_spin(1.1, 0.4, 1.1);
	
	cy1.setPosition(1.1, 0, 1.1);
	cy1.draw();
	glPopMatrix();

	//front left(seen from initial position)
	glPushMatrix();
	Cylinder cy2;
	cy2.set_Dimension(0.4, 0.1, 100, 10);
	cy2.setColor(145,207,255);

	glTranslated(1.1, 0.4, -1.1);
	glRotated(-steering, 0, 1, 0);
	glTranslated(-1.1, -0.4, 1.1);

	jud_spin(1.1, 0.4, -1.1);

	cy2.setPosition(1.1, 0, -1.1);
	cy2.draw();
	glPopMatrix();



	//back right(seen from initial position)

	glPushMatrix();
	Cylinder cy3;
	cy3.set_Dimension(0.8, 0.1, 100, 10);
	cy3.setColor(255, 224, 147);

	jud_spin(-1.1, 0.8, -1.1);

	cy3.setPosition(-1.1, 0, -1.1);
	cy3.draw();
	glPopMatrix();

	
	//back left(seen from initial position)

	glPushMatrix();
	Cylinder cy4;
	cy4.set_Dimension(0.8, 0.1, 100, 10);
	cy4.setColor(255, 224, 147);

	jud_spin(-1.1, 0.8, 1.1);

	cy4.setPosition(-1.1, 0, 1.1);
	cy4.draw();
	glPopMatrix();

	// for test rotate //////////////////////////////////////////////////////////////////////////////////////
	
	glPushMatrix();
	Rectangular F_R;
	F_R.setLength(0.5, 0.1, 0.2);
	F_R.setColor(1, 1, 1);

	glTranslated(1.1, 0.4, 1.45);
	glRotated(-steering, 0, 1, 0);
	glTranslated(-1.1, -0.4, -1.45);

	jud_spin(1.1, 0.4, 1.45);

	F_R.setPosition(1.1, 0.4, 1.45);
	F_R.setRotation(90);
	F_R.draw();
	glPopMatrix();
///////////////////////////////////
	glPushMatrix();
	Rectangular F_L;
	F_L.setLength(0.5, 0.1, 0.2);
	F_L.setColor(1, 1, 1);

	glTranslated(1.1, 0.4, -1.45);
	glRotated(-steering, 0, 1, 0);
	glTranslated(-1.1, -0.4, 1.45);

	jud_spin(1.1, 0.4, -1.45);

	F_L.setPosition(1.1, 0.4, -1.45);
	F_L.setRotation(90);
	F_L.draw();
	glPopMatrix();
///////////////////////////////////
	glPushMatrix();
	Rectangular B_R;
	B_R.setLength(0.5,0.1,0.2);
	B_R.setColor(1, 1, 1);

	jud_spin(-1.1, 0.8, 1.45);

	B_R.setPosition(-1.1, 0.8, 1.45);
	B_R.setRotation(90);
	B_R.draw();
	glPopMatrix();
///////////////////////////////////
	glPushMatrix();
	Rectangular B_L;
	B_L.setLength(0.5, 0.1, 0.2);
	B_L.setColor(1, 1, 1);

	jud_spin(-1.1, 0.8, -1.45);

	B_L.setPosition(-1.1, 0.8, -1.45);
	B_L.setRotation(90);
	B_L.draw();
	glPopMatrix();

	glPopMatrix();



	



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
