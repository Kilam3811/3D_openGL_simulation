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


	
	// all the local drawing code
	// move back to global frame of reference
	glPopMatrix();
}
