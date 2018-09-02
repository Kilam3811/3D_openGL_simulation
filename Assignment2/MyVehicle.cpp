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


Shape* ptr = NULL;
void MyVehicle::draw()
{
	//SAMPLE CAR

	// move to the vehicle¡¦s local frame of reference
	glPushMatrix();
	positionInGL();
	// all the local drawing code


	//Body
	ptr = new Rectangular(3,1,2);
	ptr->setPosition(0, 0.4, 0);
	ptr->setColor(255, 186, 221);
	ptr->setColorInGL();
	this->addShape(ptr);


	//front right(seen from initial position)
	ptr = new Cylinder(0.4, 0.1, 100, 10);
	ptr->setColor(145,207,255);
	ptr->setPosition(1.1, 0, 1.1);
	this->addShape(ptr);


	//front left(seen from initial position)
	ptr = new Cylinder(0.4, 0.1, 100, 10);
	ptr->setColor(145,207,255);
	ptr->setPosition(1.1, 0, -1.1);
	this->addShape(ptr);

	//back right(seen from initial position)
	ptr = new Cylinder (0.8, 0.1, 100, 10);
	ptr->setColor(255, 224, 147);
	ptr->setPosition(-1.1, 0, -1.1);
	this->addShape(ptr);

	//back left(seen from initial position)
	ptr = new Cylinder (0.8, 0.1, 100, 10);
	ptr->setColor(255, 224, 147);
	ptr->setPosition(-1.1, 0, 1.1);
	this->addShape(ptr);

	//Draw all the shapes in one go
	std::vector<Shape*>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		glPushMatrix();
		(*it)->draw();
		glPopMatrix();
	}

	//Logo
	glPushMatrix();
	Rectangular rec2(1.5, 0.05, 0.05);
	rec2.setColor(0, 201, 124);
	rec2.setPosition(0.5, 1.4, 0);
	rec2.draw();
	glPopMatrix();

	glPushMatrix();
	Cylinder cy5(0.15, 0.05, 100, 10);
	cy5.setColor(17, 57, 122);
	glRotated(90, -1, 0, 0);
	cy5.setPosition(-0.7, 10, 0.1);
	
	glTranslated(0, -10.15, 1.35);
	cy5.draw();
	glPopMatrix();

	glPushMatrix();
	Cylinder cy6(0.25, 0.05, 100, 10);
	cy6.setColor(255, 255, 255);
	cy6.setPosition(-0.7, 10, 0.1);
	glRotated(90, -1, 0, 0);
	glTranslated(0, -10.25, 1.30);
	cy6.draw();

	glPopMatrix();

	glPushMatrix();
	Cylinder cy7(0.35, 0.05, 100, 10);
	cy7.setColor(17, 57, 122);
	cy7.setPosition(-0.7, 10, 0.13);
	glRotated(90, -1, 0, 0);
	glTranslated(0, -10.35, 1.25);
	cy7.draw();
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


	/*ptr = new Rectangular(10,10,10);
	ptr->setPosition(-20, 0, 0);
	ptr->setColor(100, 112, 11);
	this->addShape(ptr);

	ptr = new Triangular(10, 15, 10, PI / 4);
	ptr->setColor(10, 110, 1);
	ptr->setPosition(10, 0, 0);
	

	this->addShape(ptr);

	std::vector<Shape*>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		glPushMatrix();
		(*it)->draw();
		glPopMatrix();
	}*/

	glPopMatrix();
	

}
