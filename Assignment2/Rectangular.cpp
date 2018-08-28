#pragma once
#include "Rectangular.h"

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

void Rectangular::setLength(double x_, double y_, double z_)
{
	x_length = x_;
	y_length = y_;
	z_length = z_;
}

void Rectangular::draw()
{
	
	//Draw 4 sides of the rectangle
	//Calculating the offset realtive to the origin of the rectangle
	glBegin(GL_POLYGON);
	glVertex3d(get_x_length()/2,get_y_length(), -get_z_length()/2);
	glVertex3d(get_x_length()/2,get_y_length(), -get_z_length()/2);
	glVertex3d(get_x_length()/2, 0, -get_z_length()/2);
	glVertex3d(get_x_length()/2, 0, -get_z_length()/2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(get_x_length()/2, get_y_length(), get_z_length()/2);
	glVertex3d(get_x_length()/2, 0, get_z_length() / 2);
	glVertex3d(get_x_length()/2, 0,-get_z_length()/2);
	glVertex3d(get_x_length()/2, get_y_length(), -get_z_length()/2);
	//setColorInGL();
	glEnd();
	glBegin(GL_QUADS);
	glVertex3d(-get_x_length() / 2, 0, get_z_length() / 2);
	glVertex3d(-get_x_length() / 2, get_y_length(), +get_z_length() / 2);
	glVertex3d(-get_x_length() / 2, get_y_length(), -get_z_length() / 2);
	glVertex3d(-get_x_length() / 2, 0, -get_z_length() / 2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(-get_x_length() / 2, 0,get_z_length() / 2);
	glVertex3d(-get_x_length() / 2, get_y_length(), get_z_length() / 2);
	glVertex3d(get_x_length() / 2,get_y_length(), get_z_length() / 2);
	glVertex3d(get_x_length() / 2, 0, get_z_length() / 2);
	glEnd();
	//=======================================================================
	//Draw Top and bottom layer of the rectangle
	//TOP LAYER
	glBegin(GL_QUADS);
	glVertex3d(-get_x_length() / 2, get_y_length(), get_z_length() / 2);
	glVertex3d(-get_x_length() / 2, get_y_length(), -get_z_length() / 2);
	glVertex3d(get_x_length() / 2, get_y_length(), -get_z_length() / 2);
	glVertex3d(get_x_length() / 2, get_y_length(), get_z_length() / 2);
	glEnd();

	//BOTTOM LAYER
	glBegin(GL_QUADS);
	glVertex3d(-get_x_length() / 2, 0, getZ()+get_z_length() / 2);
	glVertex3d(-get_x_length() / 2, 0, getZ()-get_z_length() / 2);

	glVertex3d(get_x_length() / 2, 0, -get_z_length() / 2);
	glVertex3d(get_x_length() / 2, 0, get_z_length() / 2);
	glEnd();

}
double Rectangular::get_x_length()
{
	return x_length;
}

double Rectangular::get_y_length()
{
	return y_length;
}

double Rectangular::get_z_length()
{
	return z_length;
}
