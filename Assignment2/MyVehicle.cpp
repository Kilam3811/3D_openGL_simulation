#include "MyVehicle.h"
#include "Triangular.h"
#include "Rectangular.h"
#include "Cylinder.h"
#include "Trapezoidal.h"
#include "VectorMaths.hpp"
#include "Messages.hpp"
#include "RemoteDataManager.hpp"
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

	
	ptr = new Trapezoidal (1.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	ptr->setColor(10, 201, 124);
	ptr->setPosition(0.5, 1.4, 0);
	addShape(ptr);

	
	ptr = new Triangular (0.5, 1.5, 0.5, PI / 6);
	ptr->setColor(100, 11, 124);
	ptr->setPosition(0.5, 1.9, 0);
	addShape(ptr);

}

void MyVehicle::draw()
{

	std::vector<Shape *>::iterator it;
	double flag = 0;
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		//Vehicle* temp_ptr = dynamic_cast<Vehicle*> (*it);
		Cylinder* temp_ptr = dynamic_cast<Cylinder*> (*it);
		if (*it != NULL) {
			if (getSteering() > 0) {
				//Draw a new one??

				glPushMatrix();
				
				positionInGL();
				//setRotation(getSteering());
				(*it)->draw();
				glPopMatrix();
				std::cout << "Streeing at " << getSteering() << std::endl;
			}
			else if (getSteering() < 0) {
				//Draw a new one??

				glPushMatrix();
				
				positionInGL();
				//setRotation(getSteering());
				(*it)->draw();

				//glTranslated(-shape_->getX(), -shape_->getY(), shape_->getZ());
				glPopMatrix();
				std::cout << "Streeing at " << getSteering() << std::endl;
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
	}
}

void MyVehicle::turning_effect(Shape* shape_)
{
	Cylinder *cyl = static_cast<Cylinder *> (shape_);
	
	
}
