#include "MyVehicle.h"
#include "Triangular.h"
#include "Rectangular.h"
#include "Cylinder.h"
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
void MyVehicle::draw()
{
	// move to the vehicle¡¦s local frame of reference
	glPushMatrix();
	positionInGL();
	//We can put our shapes in to a array and print them out.??

	//Body
	Rectangular rec1;
	rec1.setLength(2, 1, 1);
	rec1.setPosition(0, 0.25, 0);
	rec1.positionInGL();
	rec1.draw();

	//Everything realtive to the rectangle
	Triangular tri1;
	tri1.set_dimension(1, sqrt(0.5*0.5 + 1), 1, 0.46364709);
	tri1.setPosition(1.5, -0.5, 0);
	tri1.setColor(123, 11, 1);
	glRotated(180, -1, 0, 0);
	tri1.positionInGL();
	tri1.setColorInGL();
	tri1.draw();

	Triangular tri2;
	tri2.set_dimension(1, sqrt(0.5*0.5 + 1), 1, 0.46364709);
	tri2.setPosition(0, 0, 0);
	tri2.setColor(130, 110, 1);
	glRotated(180, -1, 0, 0);
	tri2.positionInGL();
	tri2.setColorInGL();
	tri2.draw();

	//Back
	glPushMatrix();
	//everthing relative to the triangle
	Rectangular rec2;
	rec2.setLength(1, 0.5, 1);
	rec2.setPosition(-3, -0.5, 0);
	rec2.positionInGL();
	rec2.setColor(0, 123, 141);
	rec2.setColorInGL();
	rec2.draw();
	glPopMatrix();
	// all the local drawing code
	// move back to global frame of reference

	//Base
	glPushMatrix();
	Rectangular rec3;
	rec3.setLength(1.5, 0.2, 1);
	rec3.setPosition(0, 0.1, 0);
	rec3.positionInGL();
	rec3.setColor(0, 123, 141);
	rec3.setColorInGL();
	rec3.draw();


	Cylinder cy1;
	cy1.set_Dimension(0.25, 0.2, 100, 10);
	cy1.setColor(255, 255, 255);
	cy1.setPosition(0.29, -0.2, -0.7);
	cy1.positionInGL();
	cy1.setColorInGL();
	cy1.draw();

	Cylinder cy2;
	cy2.set_Dimension(0.25, 0.2, 100, 10);
	cy2.setColor(255, 255, 255);
	cy2.setPosition(0, -0.3, 1);
	cy2.positionInGL();
	cy2.setColorInGL();
	cy2.draw();

	Cylinder cy3;
	cy3.set_Dimension(0.25, 0.2, 100, 10);
	cy3.setColor(255, 255, 255);
	cy3.setPosition(-1, -0.3, -0.2);
	cy3.positionInGL();
	cy3.setColorInGL();
	cy3.draw();

	Cylinder cy4;
	cy4.set_Dimension(0.25, 0.2, 100, 10);
	cy4.setColor(255, 255, 255);
	cy4.setPosition(0, -0.2, -1.4);
	cy4.positionInGL();
	cy4.setColorInGL();
	cy4.draw();
	glPopMatrix();

	//Bottom Back
	glPushMatrix();
	Rectangular rec4;
	rec4.setLength(0.67, 0.25, 1);
	rec4.setPosition(-1.111, 0, 0);
	rec4.positionInGL();
	rec4.setColor(123, 0, 141);
	rec4.setColorInGL();
	rec4.draw();
	glPopMatrix();


}
