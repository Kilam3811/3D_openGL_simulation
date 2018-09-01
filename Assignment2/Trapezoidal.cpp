#include "Trapezoidal.h"
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

void Trapezoidal::setLength(double a_length_,double b_length_, double height_, double depth_,double a_offset_,double b_offset_)
{
	a_length = a_length_;
	height = height_;
	b_length = b_length_;
	depth = depth_;
	a_offset = a_offset_;
	b_offset = b_offset_;
}

void Trapezoidal::draw()
{
	//Draw 4 sides of the trapezoidal
	//Calculating the offset realtive to the origin of the rectangle

	//Front
	glBegin(GL_QUADS);
	glVertex3d(get_a_length() / 2, 0, -get_depth() / 2);
	glVertex3d(-get_a_length() / 2, 0, -get_depth() / 2);
	glVertex3d(-get_b_length() / 2, get_height(), -get_depth() / 2);
	glVertex3d(get_b_length() / 2, get_height(), -get_depth() / 2);
	glEnd();

	//Left side
	glBegin(GL_QUADS);
	glVertex3d(get_a_length() / 2, 0, get_depth() / 2);
	glVertex3d(get_a_length() / 2, 0, -get_depth() / 2);
	glVertex3d(get_b_length() / 2, get_height(), -get_depth() / 2);
	glVertex3d(get_b_length() / 2, get_height(), get_depth() / 2);
	glEnd();
	
	//Right side
	glBegin(GL_QUADS);
	glVertex3d(-get_a_length() / 2, 0, get_depth() / 2);
	glVertex3d(-get_a_length() / 2, 0, -get_depth() / 2);
	glVertex3d(-get_b_length() / 2, get_height(), -get_depth() / 2);
	glVertex3d(-get_b_length() / 2, get_height(), get_depth() / 2);

	glEnd();
	//Back
	glBegin(GL_QUADS);
	glVertex3d(get_a_length() / 2, 0, get_depth() / 2);
	glVertex3d(-get_a_length() / 2, 0, get_depth() / 2);
	glVertex3d(-get_b_length() / 2, get_height(), get_depth() / 2);
	glVertex3d(get_b_length() / 2, get_height(), get_depth() / 2);
	glEnd();
	//=======================================================================
	//Draw Top and bottom layer of the rectangle
	//TOP LAYER
	glBegin(GL_QUADS);
	glVertex3d(get_b_length() / 2, get_height(), -get_depth() / 2);
	glVertex3d(-get_b_length() / 2, get_height(), -get_depth() / 2);
	glVertex3d(-get_b_length() / 2, get_height(), get_depth()/ 2);
	glVertex3d(get_b_length() / 2, get_height(), get_depth() / 2);
	glEnd();

	//BOTTOM LAYER
	glBegin(GL_QUADS);
	glVertex3d(get_a_length() / 2, 0, get_depth() / 2);
	glVertex3d(get_a_length() / 2, 0, -get_depth() / 2);

	glVertex3d(-get_a_length() / 2, 0, -get_depth() / 2);
	glVertex3d(-get_a_length() / 2, 0, get_depth() / 2);
	glEnd();
}

double Trapezoidal::get_a_length()
{
	return a_length;
}

double Trapezoidal::get_b_length()
{
	return get_a_length() - (get_a_offset() + get_b_offset());
}

double Trapezoidal::get_height()
{
	return height;
}

double Trapezoidal::get_depth()
{
	return depth;
}

double Trapezoidal::get_a_offset()
{
	return a_offset;
}

double Trapezoidal::get_b_offset()
{
	return b_offset;
}
