#include "MyVehicle.h"
#include "Triangular.h"
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
void MyVehicle::draw()
{
	// move to the vehicle¡¦s local frame of reference
	glPushMatrix();
	positionInGL();


	Triangular tri;
	tri.setPosition(0, 20, 0);

	//tri.setRotation(90);
	tri.positionInGL();
	tri.setColor(0, 2, 1);
	tri.setColorInGL();
	tri.setX_length(30);
	tri.setY_length(20);
	tri.setZ_length(20);
	tri.setTheta(60);
	tri.draw();

	Rectangular rec;
	rec.setPosition(0, -20, 0);
	rec.setColor(1, 0, 0);
	rec.setColorInGL();
	rec.setLength(30, 20, 20);

	rec.positionInGL();
	rec.draw();
	// all the local drawing code
	// move back to global frame of reference
	glPopMatrix();
}
