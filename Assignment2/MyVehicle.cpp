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

Shape *ptr = NULL;
MyVehicle::MyVehicle()
{
	//SAMPLE CAR

	//Body
	ptr = new Rectangular (3, 1, 2);
	ptr->setPosition(0, 0.4, 0);
	ptr->setColor(255, 186, 221);
	addShape(ptr);
	//front right(seen from initial position)
	ptr = new Cylinder (0.4, 0.1, 100, 10);
	ptr->setColor(145, 207, 255);
	ptr->setPosition(1.1, 0, 1.1);
	addShape(ptr);

	//front left(seen from initial position)
	ptr = new Cylinder (0.4, 0.1, 100, 10);
	ptr->setColor(145, 207, 255);
	ptr->setPosition(1.1, 0, -1.1);
	addShape(ptr);

	//back right(seen from initial position)
	ptr = new Cylinder (0.8, 0.1, 100, 10);
	ptr->setColor(255, 224, 147);
	ptr->setPosition(-1.1, 0, -1.1);
	addShape(ptr);

	//back left(seen from initial position)
	
	ptr = new Cylinder (0.8, 0.1, 100, 10);
	ptr->setColor(255, 224, 147);
	ptr->setPosition(-1.1, 0, 1.1);
	addShape(ptr);

	//Logo ======================================
	/*ptr = new Cylinder (0.15, 0.05, 100, 10);
	ptr->setColor(17, 57, 122);
	glRotated(90, -1, 0, 0);
	ptr->setPosition(-0.7, 10, 0.1);
	glTranslated(0, -10.15, 1.35);
	ptr->draw();
	addShape(ptr);

	
	ptr = new Cylinder (0.25, 0.05, 100, 10);
	ptr->setColor(255, 255, 255);
	ptr->setPosition(-0.7, 10, 0.1);
	glRotated(90, -1, 0, 0);
	glTranslated(0, -10.25, 1.30);
	addShape(ptr);

	
	ptr = new Cylinder (0.35, 0.05, 100, 10);
	ptr->setColor(17, 57, 122);
	ptr->setPosition(-0.7, 10, 0.13);
	glRotated(90, -1, 0, 0);
	glTranslated(0, -10.35, 1.25);
	addShape(ptr);*/

	
	ptr = new Trapezoidal (1.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	ptr->setColor(10, 201, 124);
	ptr->setPosition(0.5, 1.4, 0);
	addShape(ptr);

	
	ptr = new Triangular (0.5, 1.5, 0.5, PI / 6);
	ptr->setColor(100, 101, 124);
	ptr->setPosition(0.5, 1.9, 0);
	addShape(ptr);

}

void MyVehicle::draw()
{
	std::vector<Shape *>::iterator it;
	
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		glPushMatrix();
		positionInGL();
		(*it)->draw();
		glPopMatrix();
	}

}
