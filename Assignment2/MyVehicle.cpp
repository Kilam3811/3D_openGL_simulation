#include "MyVehicle.h"
#include "Triangular.h"
#include "Rectangular.h"
#include "Cylinder.h"
#include "Trapezoidal.h"
#include "VectorMaths.hpp"
#include "Messages.hpp"
#include "RemoteDataManager.hpp"
#include "Remote.h"
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
	ptr->setPosition(1.1, 0.2, 1.1);
	addShape(ptr);

	//front left(seen from initial position)
	ptr = new Cylinder (0.4, 0.1, 100, 10);
	ptr->setColor(145, 207, 255);
	ptr->setPosition(1.1, 0.2, -1.1);
	addShape(ptr);

	//back right(seen from initial position)
	ptr = new Cylinder (0.8, 0.1, 100, 10);
	ptr->setColor(255, 224, 147);
	ptr->setPosition(-1.1, 0.4, -1.1);
	addShape(ptr);

	//back left(seen from initial position)
	
	ptr = new Cylinder (0.8, 0.1, 100, 10);
	ptr->setColor(255, 224, 147);
	ptr->setPosition(-1.1, 0.4, 1.1);
	addShape(ptr);

	
	ptr = new Trapezoidal (1.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	ptr->setColor(10, 201, 124);
	ptr->setPosition(0.5, 1.4, 0);
	addShape(ptr);

	
	ptr = new Triangular (0.5, 1.5, 0.5, PI / 6);
	ptr->setColor(100, 11, 124);
	ptr->setPosition(0.5, 1.9, 0);
	addShape(ptr);

	//SPOKES
	ptr = new Rectangular(cos(PI/4)*0.5, sin(PI / 4)*0.5, 0.8);
	ptr->setPosition(-1.1, 0.2, -(0.4+1.1));
	ptr->setColor(244, 119, 66);
	addShape(ptr);


	ptr = new Rectangular(cos(PI / 4)*0.5, sin(PI / 4)*0.5, 0.8);
	ptr->setPosition(-1.1, 0.4, (0.4 + 1.1));
	ptr->setColor(244, 119, 66);
	addShape(ptr);

	ptr = new Rectangular(cos(PI / 4)*0.3, sin(PI / 4)*0.3, 0.8);
	ptr->setPosition(1.1, 0.2, (0.4 + 1.1));
	ptr->setColor(244, 119, 66);
	addShape(ptr);

	ptr = new Rectangular(cos(PI / 4)*0.3, sin(PI / 4)*0.3, 0.8);
	ptr->setPosition(1.1, 0.2, -(0.4 + 1.1));
	ptr->setColor(244, 119, 66);
	addShape(ptr);
}

static double temp = 0;
void MyVehicle::draw()
{
	std::vector<Shape *>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		Cylinder* cyl = dynamic_cast<Cylinder*> (*it);
		//Check if it is a cylinder
		if (cyl != NULL) {
			//If it is turning and does not move. adjust the angle
			if (getSteering() != 0 && getSpeed() == 0) {
				//Indicating the front wheel
				if ((*it)->getX() == 1.1) {
					glPushMatrix();
					positionInGL();
					(*it)->setRotation(getSteering());
					//Also has to be rolling
					cyl->draw();
					glPopMatrix();
				}
				//If it is not front wheel
				else {
					//Also has to be rolling
					glPushMatrix();
					positionInGL();
					//Needs to be rolling......
					//std::cout << "steering at " << getSteering() << std::endl;
					(*it)->setRotation(0);
					cyl->draw();
					//glTranslated(0, -(*it)->getY(), 0);
					glPopMatrix();
				}

			}
			else if (getSpeed() != 0) {
				//Indicating the front wheel
				if ((*it)->getX() == 1.1) {
					glPushMatrix();
					positionInGL();
					(*it)->setRotation(getSteering());
					//Also has to be rolling
					cyl->draw_rolling();
					glPopMatrix();
				}
				//If it is not front wheel
				else {
					//Also has to be rolling
					glPushMatrix();
					positionInGL();
					//Needs to be rolling......
					//std::cout << "steering at " << getSteering() << std::endl;
					(*it)->setRotation(0);
					//glRotated(temp, 0, 0, -1);

					//temp += 2;
					//if (temp > 360) temp = 0;
					cyl->draw_rolling();
					//glTranslated(0, -(*it)->getY(), 0);
					glPopMatrix();
				}
			}
		}
		Rectangular* rec = dynamic_cast<Rectangular*> (*it);
		if (rec != NULL) {
			//Back wheel
			if (((rec->getX() == -1.1 && (rec->getZ() == -(0.4 + 1.1)) || (rec->getZ() == (0.4 + 1.1))))) {
					glPushMatrix();
					positionInGL();

					double back_radius = 0.8;

					double instant_distance = getSpeed() * time_elapsed;
					static double total_distance = 0;
					total_distance += instant_distance;
					double theta = total_distance / back_radius;

					theta *= 180 / PI;

					rec->setRotation(theta);
					rec->draw_rolling();
					glPopMatrix();
			}
			//front wheel
			else if ((rec->getX() == 1.1 && (rec->getZ() == -(0.4 + 1.1)) || rec->getZ() == (0.4 + 1.1))) {
				glPushMatrix();
				positionInGL();

				double front_radius = 0.4;

				double instant_distance = getSpeed() * time_elapsed;
				static double total_distance = 0;
				total_distance += instant_distance;
				double theta = total_distance / front_radius;

				theta *= 180 / PI;
				rec->setRotation(theta);
				rec->draw_rolling();
				glPopMatrix();
			}
			else {
				glPushMatrix();
				positionInGL();
				(*it)->draw();
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
	//static double count = 0;
	std::vector<ShapeInit>::iterator shape_it;
	for (shape_it = cars_shapeInit.begin(); shape_it != cars_shapeInit.end(); shape_it++) {
		if (shape_it->params.cyl.isSteering&&shape_it->xyz[0] == cyl->getX() && shape_it->xyz[1] == cyl->getY() && shape_it->xyz[2] == cyl->getZ()) {
			return TRUE;
		}
	};
	return FALSE;
}