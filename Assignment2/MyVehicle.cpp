#include "MyVehicle.h"
#include "Triangular.h"
#include "Rectangular.h"
#include "Cylinder.h"
#include "Trapezoidal.h"
#include "VectorMaths.hpp"
#include "Messages.hpp"
#include "RemoteDataManager.hpp"
#include "Remote.h"
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

Shape *ptr = NULL;
#define MAX_COLOUR 255.0
#define BIG_NUM 0xfffff
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

	//front right(seen from initial position)
	ptr = new Cylinder (0.4, 0.1, 100, 10);
	ptr->setColor(145, 207, 255);
	ptr->setPosition(1.1, 0, -1.1);
	addShape(ptr);

	//back left(seen from initial position)
	ptr = new Cylinder (0.8, 0.1, 100, 10);
	ptr->setColor(255, 224, 147);
	ptr->setPosition(-1.1, 0, -1.1);
	addShape(ptr);

	//back left(seen from initial position)
	
	ptr = new Cylinder (0.8, 0.1, 100, 10);
	ptr->setColor(255, 224, 147);
	ptr->setPosition(-1.1, 0, 1.1);
	addShape(ptr);
	
	ptr = new Trapezoidal (1.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	ptr->setColor(10, 201, 124);
	ptr->setPosition(0.5, 1.4, 0);
	addShape(ptr);

	
	ptr = new Triangular (0.5, 1.5, 0.5, PI / 6);
	ptr->setColor(100, 11, 124);
	ptr->setPosition(0.5, 1.9, 0);
	ptr->setRotation(0);
	addShape(ptr);

	ptr = new Rectangular(cos(PI / 4)*0.5, sin(PI / 4)*0.5, 0.8);
	ptr->setColor(123, 11, 41);
	ptr->setPosition(-1.1, 0.4, -(0.4 + 1.1));
	addShape(ptr);

	ptr = new Rectangular(cos(PI / 4)*0.5, sin(PI / 4)*0.5, 0.8);
	ptr->setColor(123, 11, 41);
	ptr->setPosition(1.1, 0.4, -(0.4 + 1.1));
	addShape(ptr);

	ptr = new Rectangular(cos(PI / 4)*0.5, sin(PI / 4)*0.5, 0.8);
	ptr->setColor(123, 11, 41);
	ptr->setPosition(1.1, 0.4, (0.4 + 1.1));
	addShape(ptr);

	ptr = new Rectangular(cos(PI / 4)*0.5, sin(PI / 4)*0.5, 0.8);
	ptr->setColor(123, 11, 41);
	ptr->setPosition(-1.1, 0.4, (0.4 + 1.1));
	addShape(ptr);

}

static double total_distance = 0;
void MyVehicle::draw()
{
	std::vector<Shape *>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		Cylinder* cyl = dynamic_cast<Cylinder*> (*it);
		//Check if it is a cylinder
		if (cyl != NULL) {
			//If it is turning and does not move. adjust the angle
			if (getSteering() != 0) {
				//Indicating the front wheel
				if ((*it)->getX() == 1.1) {
					glPushMatrix();
					positionInGL();
					cyl->setRotation(getSteering());
					cyl->draw();
					glPopMatrix();
				}
				//If it is not front wheel
				else {
					//Also has to be rolling
					glPushMatrix();
					positionInGL();
					cyl->draw();
					glPopMatrix();
				}

			}
			else if (getSpeed() != 0) {
				//Indicating the front wheel
				if (cyl->getX() == 1.1) {
					glPushMatrix();
					positionInGL();
					cyl->draw();
					glPopMatrix();
				}
				//If it is not front wheel
				else {
					//Also has to be rolling
					glPushMatrix();
					positionInGL();
					cyl->draw();
					glPopMatrix();
				};
			}
			else {
				glPushMatrix();
				positionInGL();
				cyl->draw();
				glPopMatrix();
			}
		}
		//Rectangular prisms are my spokes..
		Rectangular* rec = dynamic_cast<Rectangular*> (*it);
		if (rec != NULL) {
			// if it is front
			if (rec->getX() == 1.1) {
				glPushMatrix();
				positionInGL();
				//Calulate how much the wheel has been rotating.
				double radius = 0.4;
				double instant_distance = getSpeed() * time_elapsed;
				total_distance += instant_distance;
				if (total_distance > BIG_NUM) {
					total_distance = 0;
				}
				double theta = total_distance / radius;
				theta *= 180 / PI;
				rec->setRotation(theta);
				rec->draw_rolling();
				glPopMatrix();
			}
			else if(rec->getX() == -1.1) {
				glPushMatrix();
				positionInGL();
				//Calulate how much the wheel has been rotating.
				double radius = 0.8;
				double instant_distance = getSpeed() * time_elapsed;
				total_distance += instant_distance;
				double theta = total_distance / radius;
				if (total_distance > BIG_NUM) {
					total_distance = 0;
				}
				theta *= 180 / PI;
				rec->setRotation(theta);
				rec->draw_rolling();
				glPopMatrix();
			}
			//If it is not a spoke then draw it normally.
			else {
				glPushMatrix();
				positionInGL();
				rec->setRotation(0);
				rec->draw();
				glPopMatrix();
			}
		}
		
		else {
			glPushMatrix();
			positionInGL();
			(*it)->draw();
			glPopMatrix();
		}
	};
}
bool MyVehicle::check_front_wheel(Cylinder * cyl) {
	std::vector<ShapeInit>::iterator shape_it;
	for (shape_it = cars_shapeInit.begin(); shape_it != cars_shapeInit.end(); shape_it++) {
		if (shape_it->params.cyl.isSteering&&shape_it->xyz[0] == cyl->getX() && shape_it->xyz[1] == cyl->getY() && shape_it->xyz[2] == cyl->getZ()) {
			return TRUE;
		}
	};
	return FALSE;
}