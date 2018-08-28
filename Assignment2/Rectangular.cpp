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
