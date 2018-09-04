#include "MyVehicle.h"
#include "Triangular.h"
#include "Rectangular.h"
#include "Cylinder.h"
#include "Trapezoidal.h"
#include "VectorMaths.hpp"
#include "Messages.hpp"
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

	
	ptr = new Trapezoidal (1.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	ptr->setColor(10, 201, 124);
	ptr->setPosition(0.5, 1.4, 0);
	addShape(ptr);

	
	ptr = new Triangular (0.5, 1.5, 0.5, PI / 6);
	ptr->setColor(100, 11, 124);
	ptr->setPosition(0.5, 1.9, 0);
	addShape(ptr);

}

MyVehicle::MyVehicle(VehicleModel * vm, ShapeInit * init)
{
	/*std::vector<Shape*>::iterator it;
	//Assume the exteral car would have one shape for now?..
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		//Might optimized a bit later...
		Rectangular* rec = dynamic_cast<Rectangular*> (*it);
		if ((*it) != NULL) {
			init->type = RECTANGULAR_PRISM;
			init->xyz[0] = rec->getX();
			init->xyz[1] = rec->getY();
			init->xyz[2] = rec->getZ();
			init->rgb[0] = rec->getRed();
			init->rgb[1] = rec->getGreen();
			init->rgb[2] = rec->getBlue();
			init->rotation = rec->getRotation();
			init->params.rect.xlen = rec->get_x_length();
			init->params.rect.ylen = rec->get_y_length();
			init->params.rect.zlen = rec->get_z_length();
		}

		Cylinder* cyl = dynamic_cast<Cylinder*> (*it);
		if ((*it) != NULL) {
			init->type = CYLINDER;
			init->xyz[0] = cyl->getX();
			init->xyz[1] = cyl->getY();
			init->xyz[2] = cyl->getZ();
			init->rgb[0] = cyl->getRed();
			init->rgb[1] = cyl->getGreen();
			init->rgb[2] = cyl->getBlue();
			init->rotation = cyl->getRotation();
			init->params.cyl.depth = cyl->getHeight();
			init->params.cyl.radius = cyl->getRadius();
		}
		Triangular* tri = dynamic_cast<Triangular*> (*it);
		if ((*it) != NULL) {
			init->type = TRIANGULAR_PRISM;
			init->xyz[0] = tri->getX();
			init->xyz[1] = tri->getY();
			init->xyz[2] = tri->getZ();
			init->rgb[0] = tri->getRed();
			init->rgb[1] = tri->getGreen();
			init->rgb[2] = tri->getBlue();
			init->rotation = tri->getRotation();
			init->params.tri.alen = tri->getX_length();
			init->params.tri.blen = tri->getY_length();
			init->params.tri.angle = tri->getTheta();
			init->params.tri.depth = tri->getZ_length();
		}
		Trapezoidal* tra = dynamic_cast<Trapezoidal*> (*it);
		if ((*it) != NULL) {
			init->type = TRAPEZOIDAL_PRISM;
			init->xyz[0] = tra->getX();
			init->xyz[1] = tra->getY();
			init->xyz[2] = tra->getZ();
			init->rgb[0] = tra->getRed();
			init->rgb[1] = tra->getGreen();
			init->rgb[2] = tra->getBlue();
			init->rotation = tra->getRotation();
			init->params.trap.alen = tra->get_a_length();
			init->params.trap.blen = tra->get_b_length();
			init->params.trap.aoff = tra->get_a_offset();
			init->params.trap.depth = tra->get_depth();
			init->params.trap.height = tra->get_height();
		}
	}*/
}

void MyVehicle::draw()
{
	std::vector<Shape *>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		//Vehicle* temp_ptr = dynamic_cast<Vehicle*> (*it);
		Cylinder* temp_ptr = dynamic_cast<Cylinder*> (*it);
		if (*it != NULL) {
			glPushMatrix();
			turning_effect();
			positionInGL();
			(*it)->draw();
			glPopMatrix();
		}
		else {
			glPushMatrix();
			//turning_effect();
			positionInGL();
			(*it)->draw();
			glPopMatrix();
		}
	}
	
}

void MyVehicle::turning_effect()
{
	if (getSteering() != 0) {
		//std::cout << "turning at" << getSteering() << std::endl;
	}
	/*if (getSteering() > 0) {
		setRotation(getSteering());
	}
	else if(getSteering() < 0){
		setRotation(getSteering());
	}
	else {
		setRotation(0);
	}*/
}
