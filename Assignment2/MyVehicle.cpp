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

}

static double temp = 0;
void MyVehicle::draw()
{
	std::vector<Shape *>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		Cylinder* cyl = dynamic_cast<Cylinder*> (*it);
		//Check if it is a cylinder
		if (cyl != NULL) {
			//If it is turning. adjust the angle
			if (getSteering() != 0) {
				//Indicating the front wheel
				if ((*it)->getX() == 1.1) {
					glPushMatrix();
					positionInGL();
					(*it)->setRotation(getSteering());
					//Also has to be rolling
					(*it)->draw();
					glPopMatrix();
				}
				//If it is not front wheel
				else {
					//Also has to be rolling
					glPushMatrix();
					positionInGL();


					(*it)->setRotation(temp);
					temp += 2;
					if (temp > 360) temp = 0;

					//Needs to be rolling......
					//std::cout << "steering at " << getSteering() << std::endl;
					(*it)->draw();
					//glTranslated(0, -(*it)->getY(), 0);
					glPopMatrix();
				}

			}
			//else keeps rolling or stop?
			else {
				glPushMatrix();
				positionInGL();
				(*it)->setRotation(getSteering());

				//Needs to be rolling......
				//std::cout << "steering at " << getSteering() << std::endl;
				(*it)->draw();
				//glTranslated(0, -(*it)->getY(), 0);
				glPopMatrix();
			}
		}
		else {
			glPushMatrix();
			positionInGL();
			//positionInGL();
			//setColorInGL();
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