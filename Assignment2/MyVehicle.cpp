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

	// all the local drawing code
	// move back to global frame of reference
	//We can put our shapes in to a array and print them out.??
	//Body
	Rectangular rec1;
	rec1.setLength(2, 1, 1);
	rec1.setColor(255, 217, 84);
	rec1.setPosition(-10, 0.25, 0);
	rec1.positionInGL();
	rec1.setColorInGL();
	rec1.draw();

	//Everything realtive to the rectangle
	Triangular tri1;
	tri1.set_dimension(1, sqrt(0.5*0.5 + 1), 1, 0.46364709);
	tri1.setPosition(1.5, -0.5, 0);
	tri1.setColor(66, 197, 244);
	glRotated(180, -1, 0, 0);
	tri1.positionInGL();
	tri1.setColorInGL();
	tri1.draw();

	Triangular tri2;
	tri2.set_dimension(1, sqrt(0.5*0.5 + 1), 1, 0.46364709);
	tri2.setPosition(0, 0, 0);
	tri2.setColor(66, 197, 244);
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
	
	//Base
	//glPushMatrix();
	/*Rectangular rec3;
	rec3.setLength(1.5, 0.2, 1);
	rec3.setPosition(-1.5, -0.25, 0);
	rec3.positionInGL();
	rec3.setColor(0, 123, 141);
	rec3.setColorInGL();
	rec3.draw();*/


	Cylinder cy1;
	cy1.set_Dimension(0.25, 0.2, 100, 10);
	cy1.setColor(255, 255, 255);
	cy1.setPosition(-1.1, -0.9, -0.7);
	cy1.positionInGL();
	cy1.setColorInGL();
	cy1.draw();

	Cylinder cy2;
	cy2.set_Dimension(0.25, 0.2, 100, 10);
	cy2.setColor(255, 255, 255);
	cy2.setPosition(0, -0.25, 1);
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
	//glPopMatrix();
	
	//Bottom Back
	/*glPushMatrix();
	Rectangular rec4;
	rec4.setLength(0.67, 0.25, 1);
	rec4.setPosition(-1.111, 0, 0);
	rec4.positionInGL();
	rec4.setColor(123, 0, 141);
	rec4.setColorInGL();
	rec4.draw();
	glPopMatrix();*/


	glPushMatrix();
	Trapezoidal trap1;
	trap1.setLength(1, 0.5, 0.5, 1);
	trap1.setPosition(-0.9, 0.65, 0.5);
	trap1.positionInGL();
	trap1.setColor(255, 255, 255);
	trap1.setColorInGL();
	trap1.draw();

	Triangular tri3;
	tri3.set_dimension(0.5, sqrt(0.25*0.25 + 1), 1, PI/4); 
	tri3.setPosition(0, 0.5, 0);
	tri3.setColor(226, 51, 45);
	tri3.positionInGL();
	tri3.setColorInGL();
	tri3.draw();
	glPopMatrix();


	glPushMatrix();
	Cylinder cy5;
	cy5.set_Dimension(0.15, 0.05, 100, 10);
	cy5.setColor(17, 57, 122);
	cy5.setPosition(0.5, 9.5, -0.05);
	glRotated(90, -1, 0, 0);
	glTranslated(0, -10.15, 1.35);
	cy5.positionInGL();
	cy5.setColorInGL();
	cy5.draw();
	glPopMatrix();

	glPushMatrix();
	Cylinder cy6;
	cy6.set_Dimension(0.25, 0.05, 100, 10);
	cy6.setColor(255, 255, 255);
	cy6.setPosition(0.5, 9.5, -0.05);
	glRotated(90, -1, 0, 0);
	glTranslated(0, -10.25, 1.30);
	cy6.positionInGL();
	cy6.setColorInGL();
	cy6.draw();

	glPopMatrix();

	glPushMatrix();
	Cylinder cy7;
	cy7.set_Dimension(0.35, 0.05, 100, 10);
	cy7.setColor(17, 57, 122);
	cy7.setPosition(0.5, 9.5, -0.05);
	glRotated(90, -1, 0, 0);
	glTranslated(0, -10.35, 1.25);
	cy7.positionInGL();
	cy7.setColorInGL();
	cy7.draw();
	glPopMatrix();

	glPopMatrix();
}
