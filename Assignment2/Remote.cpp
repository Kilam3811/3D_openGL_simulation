#include "Remote.h"
#include "Shape.hpp"
#include <cassert>
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
Shape * shape_ptr = NULL;
Remote::Remote(VehicleModel vm_)
{
	//Each model has a vector, which contains informations about the shapes..
	vm = vm_;
	std::vector<ShapeInit>::iterator it;
	//Assume the exteral car would have one shape for now?..
	for (it = vm.shapes.begin(); it != vm.shapes.end(); ++it)
		//Might optimized a bit later...
		if (it->type == RECTANGULAR_PRISM) {
			double xLength = it->params.rect.xlen;
			double yLength = it->params.rect.ylen;
			double zLength = it->params.rect.zlen;
			double red = it->rgb[0];
			double green = it->rgb[1];
			double blue = it->rgb[2];
			double x_cor = it->xyz[0];
			double y_cor = it->xyz[1];
			double z_cor = it->xyz[2];
			double angle = it->rotation;
			add_to_shapeInit_list(*it);
			draw_rec(xLength, yLength, zLength, red, green, blue, x_cor, y_cor, z_cor, angle);
		}
		else if (it->type == CYLINDER) {
			double radius = it->params.cyl.radius;
			double depth = it->params.cyl.depth;
			double red = it->rgb[0];
			double green = it->rgb[1];
			double blue = it->rgb[2];
			double x_cor = it->xyz[0];
			double y_cor = it->xyz[1];
			double z_cor = it->xyz[2];
			double rotate_angle = it->rotation;
			add_to_shapeInit_list(*it);

			draw_cyl(radius, depth, red, green, blue, x_cor, y_cor, z_cor, rotate_angle);
		}
		else if (it->type == TRIANGULAR_PRISM) {
			double a_len = it->params.tri.alen;
			double b_len = it->params.tri.blen;
			double depth = it->params.tri.depth;
			double theta = it->params.tri.angle;
			double red = it->rgb[0];
			double green = it->rgb[1];
			double blue = it->rgb[2];
			double x_cor = it->xyz[0];
			double y_cor = it->xyz[1];
			double z_cor = it->xyz[2];
			double rotate_angle = it->rotation;
			add_to_shapeInit_list(*it);
			draw_tri(a_len, b_len, depth, theta, red, green, blue, x_cor, y_cor, z_cor, rotate_angle);
		}
		else if (it->type == TRAPEZOIDAL_PRISM) {
			double a_len = it->params.trap.alen;
			double b_len = it->params.trap.blen;
			double depth = it->params.trap.depth;
			double height = it->params.trap.height;
			double offset = it->params.trap.aoff;
			double red = it->rgb[0];
			double green = it->rgb[1];
			double blue = it->rgb[2];
			double x_cor = it->xyz[0];
			double y_cor = it->xyz[1];
			double z_cor = it->xyz[2];
			double rotate_angle = it->rotation;
			add_to_shapeInit_list(*it);
			draw_tra(a_len, b_len, depth, height, offset, red, green, blue, x_cor, y_cor, z_cor, rotate_angle);
		}
}

void Remote::draw()
{
	//Draw function will be keep calling...
	std::vector<Shape *>::iterator it;
	for (it = cars.begin(); it != cars.end(); ++it) {
		Cylinder* cyl = dynamic_cast<Cylinder*> (*it);
		if (cyl != NULL) {
			if (check_wheel(cyl)) {
				//std::cout << "angle at" << getSteering() << std::endl;
				glPushMatrix();
				positionInGL();
				// all the local drawing code
				//setRotation(getSteering());
				//glPushMatrix();
				
				(*it)->draw();
				//setRotation(getSteering());
				//glPopMatrix();
				// move back to global frame of reference
				glPopMatrix();
			}
			/*else {
				// move to the vehicle¡¦s local frame of reference
				glPushMatrix();
				positionInGL();
				// all the local drawing code
				(*it)->draw();
				// move back to global frame of reference
				glPopMatrix();
			}*/
		}
		else {
			// move to the vehicle¡¦s local frame of reference
			glPushMatrix();
			positionInGL();
			// all the local drawing code
			(*it)->draw();
			// move back to global frame of reference
			glPopMatrix();
		}
	}


}

void Remote::draw_rec(double xLength, double yLength, double zLength, double red, double green, double blue, double x_cor, double y_cor, double z_cor, double rotate_angle)
{
	shape_ptr = new Rectangular(xLength, yLength, zLength);
	shape_ptr->setPosition(x_cor, y_cor, z_cor);
	shape_ptr->setRotation(rotate_angle);
	shape_ptr->setColor(red, green, blue);
	add_to_draw_list(shape_ptr);
	
}

void Remote::draw_tri(double a_len, double b_len, double depth, double theta, double red, double green, double blue, double x_cor, double y_cor, double z_cor, double rotate_angle)
{
	shape_ptr = new Triangular(a_len, b_len, depth, theta);
	shape_ptr->setPosition(x_cor, y_cor, z_cor);
	shape_ptr->setRotation(rotate_angle);
	shape_ptr->setColor(red, green, blue);
	add_to_draw_list(shape_ptr);
}

void Remote::draw_tra(double a_len, double b_len, double depth, double height, double offset, double red, double green, double blue, double x_cor, double y_cor, double z_cor, double rotate_angle)
{
	shape_ptr = new Trapezoidal(a_len, b_len, height, depth, offset, offset);
	shape_ptr->setPosition(x_cor, y_cor, z_cor);
	shape_ptr->setRotation(rotate_angle);
	shape_ptr->setColor(red, green, blue);
	add_to_draw_list(shape_ptr);
}

void Remote::draw_cyl(double radius, double depth, double red, double green, double blue, double x_cor, double y_cor, double z_cor, double rotate_angle)
{
	shape_ptr = new Cylinder(radius, depth, 100, 10);
	shape_ptr->setPosition(x_cor, y_cor, z_cor);
	shape_ptr->setRotation(rotate_angle);
	shape_ptr->setColor(red, green, blue);
	add_to_draw_list(shape_ptr);
}

void Remote::add_to_draw_list(Shape * shape)
{
	cars.push_back(shape);
}

void Remote::add_to_shapeInit_list(ShapeInit init)
{
	cars_shapeInit.push_back(init);
}

bool Remote::check_wheel(Cylinder * cyl)
{
	std::vector<ShapeInit>::iterator shape_it;
	for (shape_it = cars_shapeInit.begin(); shape_it != cars_shapeInit.end(); ++shape_it) {
		if (((shape_it)->type == CYLINDER) && (shape_it)->params.cyl.radius == cyl->getRadius()) {
			if (shape_it->params.cyl.isSteering) {
				return TRUE;
			}
		}
	};
	return FALSE;
}
