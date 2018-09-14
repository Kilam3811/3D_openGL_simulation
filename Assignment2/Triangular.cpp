#include "Triangular.h"
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
Triangular::Triangular(double x_length, double y_length, double z_length, double angle)
{
	set_dimension(x_length, y_length, z_length, angle);
}
void Triangular::draw()
{	
	positionInGL();
	setColorInGL();
	//Draw two triangular sides
	glBegin(GL_TRIANGLES);
	//side
	glVertex3d(getX_length() / 2, 0, -getZ_length() / 2);
	glVertex3d(-getX_length() / 2, 0, -getZ_length() / 2);
	//modified vertix from certain angle
	glVertex3d(getNormal_X_Cor(), getNormal_Y_Cor(), -getZ_length() / 2);
	glEnd();

	glBegin(GL_TRIANGLES);
	//side
	glVertex3d(getX_length() / 2, 0, getZ_length() / 2);
	glVertex3d(-getX_length() / 2, 0, getZ_length() / 2);
	//modified vertix from certain angle
	glVertex3d(getNormal_X_Cor(), getNormal_Y_Cor(), getZ_length() / 2);
	glEnd();


	//Draw 3 square sides

	//Top layer
	glBegin(GL_QUADS);
	glVertex3d(-getX_length() / 2, 0, -getZ_length() / 2);
	glVertex3d(-getX_length() / 2, 0, getZ_length() / 2);
	glVertex3d(getNormal_X_Cor(), getNormal_Y_Cor(), getZ_length() / 2);
	glVertex3d(getNormal_X_Cor(), getNormal_Y_Cor(), -getZ_length() / 2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(getX_length() / 2, 0, getZ_length() / 2);
	glVertex3d(getX_length() / 2, 0, -getZ_length() / 2);
	glVertex3d(getNormal_X_Cor(), getNormal_Y_Cor(), -getZ_length() / 2);
	glVertex3d(getNormal_X_Cor(), getNormal_Y_Cor(), getZ_length() / 2);
	glEnd();

	//Bottom layer
	glBegin(GL_QUADS);
	glVertex3d(getX_length() / 2, 0, getZ_length() / 2);
	glVertex3d(getX_length() / 2, 0, -getZ_length() / 2);
	glVertex3d(-getX_length() / 2, 0, -getZ_length() / 2);
	glVertex3d(-getX_length() / 2, 0, getZ_length() / 2);
	glEnd();
}

void Triangular::set_dimension(double x_length, double y_length, double z_length, double angle)
{
	a_length = x_length;
	b_length = y_length;
	depth = z_length;
	//Normalized degrees to radian.
	if (angle == 90) {
		angle = PI / 2;
	}
	if (angle >= 2 * PI) {
		angle = (angle*PI) / 180;
	}
	theta = angle;
}

double Triangular::getTheta()
{
	return theta;
}

double Triangular::getX_length()
{
	return a_length;
}

double Triangular::getY_length()
{
	return b_length;
}

double Triangular::getZ_length()
{
	return depth;
}

double Triangular::getNormal_X_Cor()
{
	double x_cor;
	if (theta < PI / 2.0) {
		x_cor = (getX_length() / 2.0) - cos(theta)*getY_length();
	}
	else if (theta == PI / 2.0) {
		x_cor = getX_length() / 2.0;
	}
	else {
		double temp_angle = PI - getTheta();
		x_cor = getX_length() / 2.0 + cos(temp_angle)*getY_length();
	}
	return x_cor;
}

double Triangular::getNormal_Y_Cor()
{
	double y_cor;
	if (theta < PI / 2.0) {
		y_cor = sin(theta)*getY_length();
	}
	else if (theta == PI / 2.0) {
		y_cor = getY_length();
	}
	else {
		double temp_angle = PI - getTheta();
		y_cor = sin(temp_angle)*getY_length();
	}
	return y_cor;
}
