
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>
#include <cassert>
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#elif defined(WIN32)
	#include <Windows.h>
	#include <tchar.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#endif


#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"
#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"

//Private #include
#include "Rectangular.h"
#include "Triangular.h"
#include "Trapezoidal.h"
#include "Cylinder.h"
#include "MyVehicle.h"
#include "Remote.h"

#define MAX_COLOUR 255.0


void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
//   can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;

// default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

//int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	//   with the name of the class you want to show as the current 
	//   custom vehicle.
	// -------------------------------------------------------------------------

	vehicle = new MyVehicle();


	// add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10,-10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,-10, 1));

	// add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);	


	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

void drawGoals()
{
	for (int i = 0; i < goals.size(); ++i) {
		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}
void testing_Draw() {
	//Cylinder cyl(10, 10, 100, 10);
	//cyl.setPosition(0, 0, 0);
	//cyl.draw();
	//CUSTOMIZED VEHICLE
	//Rectangular rec(10,10,10);
	//rec.setPosition(10, 10, 0);
	//rec.draw();

	//Cylinder cyl(10, 100, 100, 10);
	//cyl.setPosition(0, 0, 0);
	//cyl.setColor(244, 121, 121);
	//cyl.draw();
	MyVehicle F1;
	F1.setPosition(0,0,0);
	//F1.positionInGL();
	F1.draw();
	//==========================================

	/*Triangular tri(1, 1, 2.5, 90);
	tri.setColor(0, 1, 0);
	tri.setRotation(0);
	tri.setPosition(0, 0, 0);
	tri.draw();*/
}


void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();
	
	// draw other vehicles
	for(std::map<int, Vehicle *>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) 
		iter->second->draw();

	// draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();

	}

	// draw obstacles
	ObstacleManager::get()->drawAll();

	//draw goals
	drawGoals();

	// draw HUD
	HUD::Draw();

	//testing_Draw();
	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;

}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if(QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {

	if (KeyManager::get()->isAsciiKeyPressed('a')) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c')) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d')) {
		Camera::get()->strafeRight();
	}

	if (KeyManager::get()->isAsciiKeyPressed('s')) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w')) {
		Camera::get()->moveForward();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ')) {
		Camera::get()->strafeUp();
	}

	speed = 0;
	steering = 0;

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;   
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}

	// attempt to do data communications every 4 frames if we've created a local vehicle
	if(frameCounter % 4 == 0 && vehicle != NULL) {

		// if not connected, attempt to connect every 2 seconds
		if(!RemoteDataManager::IsConnected()) {
			if(frameCounter % 120 == 0) {
		
				// erase other vehicles
				for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au","18081");

				// on connect, let's tell the server what we look like
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					vm.remoteID = 0;
					ShapeInit init;
					/*//Body
					ptr = new Rectangular(3, 1, 2);
					ptr->setPosition(0, 0.4, 0);
					ptr->setColor(255, 186, 221);
					addShape(ptr);*/
					init.type = RECTANGULAR_PRISM;
					init.xyz[0] = 0;
					init.xyz[1] = 0.4;
					init.xyz[2] = 0;
					init.rgb[0] = 255 / MAX_COLOUR;
					init.rgb[1] = 186 / MAX_COLOUR;
					init.rgb[2] = 221 / MAX_COLOUR;
					init.rotation = 0;
					init.params.rect.xlen = 3;
					init.params.rect.ylen = 1;
					init.params.rect.zlen = 2;
					//init.params.rect.isSpoke = FALSE;
					vm.shapes.push_back(init);

					ShapeInit init_1;
					/*//front right(seen from initial position)
					ptr = new Cylinder(0.4, 0.1, 100, 10);
					ptr->setColor(145, 207, 255);
					ptr->setPosition(1.1, 0.2, 1.1);
					addShape(ptr);*/

					init_1.type = CYLINDER;
					init_1.xyz[0] = 1.1;
					init_1.xyz[1] = 0;
					init_1.xyz[2] = 1.1;
					init_1.rgb[0] = 145/MAX_COLOUR;
					init_1.rgb[1] = 207/ MAX_COLOUR;
					init_1.rgb[2] = 255/ MAX_COLOUR;
					init_1.rotation = 0;
					init_1.params.cyl.depth = 0.1;
					init_1.params.cyl.radius = 0.4;
					init_1.params.cyl.isSteering = TRUE;
					init_1.params.cyl.isRolling = TRUE;
					//init_1.isSpoke = FALSE;
					vm.shapes.push_back(init_1);

					ShapeInit init_2;
					/*//front left(seen from initial position)
					ptr = new Cylinder(0.4, 0.1, 100, 10);
					ptr->setColor(145, 207, 255);
					ptr->setPosition(1.1, 0, -1.1);
					addShape(ptr);*/
					init_2.type = CYLINDER;
					init_2.xyz[0] = 1.1;
					init_2.xyz[1] = 0;
					init_2.xyz[2] = -1.1;
					init_2.rgb[0] = 145 / MAX_COLOUR;
					init_2.rgb[1] = 207 / MAX_COLOUR;
					init_2.rgb[2] = 255 / MAX_COLOUR;
					init_2.rotation = 0;
					init_2.params.cyl.depth = 0.1;
					init_2.params.cyl.radius = 0.4;
					init_2.params.cyl.isSteering = TRUE;
					init_2.params.cyl.isRolling = TRUE;
					//init_2.isSpoke = FALSE;
					vm.shapes.push_back(init_2);

					//back right(seen from initial position)
					/*ptr = new Cylinder(0.8, 0.1, 100, 10);
					ptr->setColor(255, 224, 147);
					ptr->setPosition(-1.1, 0, -1.1);
					addShape(ptr);*/
					ShapeInit init_3;
					init_3.type = CYLINDER;
					init_3.xyz[0] = -1.1;
					init_3.xyz[1] = 0;
					init_3.xyz[2] = -1.1;
					init_3.rgb[0] = 255 / MAX_COLOUR;
					init_3.rgb[1] = 224 / MAX_COLOUR;
					init_3.rgb[2] = 147 / MAX_COLOUR;
					init_3.rotation = 0;
					init_3.params.cyl.depth = 0.1;
					init_3.params.cyl.radius = 0.8;
					init_3.params.cyl.isSteering = FALSE;
					init_3.params.cyl.isRolling = TRUE;
					//init_3.isSpoke = FALSE;
					vm.shapes.push_back(init_3);

					/*//back left(seen from initial position)
					ptr = new Cylinder(0.8, 0.1, 100, 10);
					ptr->setColor(255, 224, 147);
					ptr->setPosition(-1.1, 0, 1.1);
					addShape(ptr);*/
					ShapeInit init_4;
					init_4.type = CYLINDER;
					init_4.xyz[0] = -1.1;
					init_4.xyz[1] = 0;
					init_4.xyz[2] = 1.1;
					init_4.rgb[0] = 255 / MAX_COLOUR;
					init_4.rgb[1] = 224 / MAX_COLOUR;
					init_4.rgb[2] = 147 / MAX_COLOUR;
					init_4.rotation = 0;
					init_4.params.cyl.depth = 0.1;
					init_4.params.cyl.radius = 0.8;
					init_4.params.cyl.isSteering = FALSE;
					init_4.params.cyl.isRolling = TRUE;
					//init_4.isSpoke = FALSE;
					vm.shapes.push_back(init_4);


					/*ptr = new Trapezoidal(1.5, 0.5, 0.5, 0.5, 0.5, 0.5);
					ptr->setColor(10, 201, 124);
					ptr->setPosition(0.5, 1.4, 0);
					addShape(ptr);*/
					ShapeInit init_5;
					init_5.type = TRAPEZOIDAL_PRISM;
					init_5.xyz[0] = 0.5;
					init_5.xyz[1] = 1.4;
					init_5.xyz[2] = 0;
					init_5.rgb[0] = 10/ MAX_COLOUR;
					init_5.rgb[1] = 201 / MAX_COLOUR;
					init_5.rgb[2] = 124 / MAX_COLOUR;
					init_5.rotation = 0;
					init_5.params.trap.alen = 1.5;
					init_5.params.trap.blen = 0.5;
					init_5.params.trap.aoff = 0.5;
					init_5.params.trap.depth = 0.5;
					init_5.params.trap.height = 0.5;
					//init_5.isSpoke = FALSE;
					vm.shapes.push_back(init_5);


					/*ptr = new Triangular(0.5, 1.5, 0.5, PI / 6);
					ptr->setColor(100, 11, 124);
					ptr->setPosition(0.5, 1.9, 0);
					addShape(ptr);*/
					ShapeInit init_6;
					init_6.type = TRIANGULAR_PRISM;
					init_6.xyz[0] = 0.5;
					init_6.xyz[1] = 1.9;
					init_6.xyz[2] = 0;
					init_6.rgb[0] = 100/ MAX_COLOUR;
					init_6.rgb[1] = 11 / MAX_COLOUR;
					init_6.rgb[2] = 124 / MAX_COLOUR;
					init_6.rotation = 0;
					init_6.params.tri.alen = 0.5;
					init_6.params.tri.blen = 1.5;
					init_6.params.tri.angle = PI / 6;
					init_6.params.tri.depth = 0.5;
					//init_6.isSpoke = FALSE;
					vm.shapes.push_back(init_6);

				

					/*ptr = new Rectangular(cos(PI / 4)*0.5, sin(PI / 4)*0.5, 0.8);
					ptr->setPosition(-1.1, 0.4, -(0.4 + 1.1));
					addShape(ptr);*/
					/*ShapeInit init_7;
					init_7.type = RECTANGULAR_PRISM;
					init_7.xyz[0] = -1.1;
					init_7.xyz[1] = 0.4;
					init_7.xyz[2] = -1.5;
					init_7.rgb[0] = 244 / MAX_COLOUR;
					init_7.rgb[1] = 119 / MAX_COLOUR;
					init_7.rgb[2] = 66 / MAX_COLOUR;
					init_7.rotation = 0;
					init_7.params.rect.xlen = cos(PI / 4)*0.5;
					init_7.params.rect.ylen = sin(PI / 4)*0.5;
					init_7.params.rect.zlen = 0.8;

					init_7.params.rect.isSpoke = TRUE;
					//init_7.params.rect.isSteering = FALSE;
					//init_7.params.rect.normal = FALSE;
					//init_7.isSpoke = TRUE;
					vm.shapes.push_back(init_7);


					/*ptr = new Rectangular(cos(PI / 4)*0.5, sin(PI / 4)*0.5, 0.8);
					ptr->setPosition(-1.1, 0.4, (0.4 + 1.1));
					addShape(ptr);
					ShapeInit init_8;
					init_8.type = RECTANGULAR_PRISM;
					init_8.xyz[0] = -1.1;
					init_8.xyz[1] = 0.4;
					init_8.xyz[2] = 1.5;
					init_8.rgb[0] = 244 / MAX_COLOUR;
					init_8.rgb[1] = 119 / MAX_COLOUR;
					init_8.rgb[2] = 66 / MAX_COLOUR;
					init_8.rotation = 0;
					init_8.params.rect.xlen = cos(PI / 4)*0.5;
					init_8.params.rect.ylen = sin(PI / 4)*0.5;
					init_8.params.rect.zlen = 0.8;
					//init_8.params.rect.isSpoke = TRUE;
					//init_8.params.rect.isSteering = FALSE;
					//init_8.params.rect.normal = FALSE;
					//init_8.isSpoke = TRUE;
					vm.shapes.push_back(init_8);

					/*ptr = new Rectangular(cos(PI / 4)*0.3, sin(PI / 4)*0.3, 0.8);
					ptr->setPosition(1.1, 0.2, (0.4 + 1.1));
					addShape(ptr);
					ShapeInit init_9;
					init_9.type = RECTANGULAR_PRISM;
					init_9.xyz[0] = 1.1;
					init_9.xyz[1] = 0.2;
					init_9.xyz[2] = 1.5;
					init_9.rgb[0] = 244 / MAX_COLOUR;
					init_9.rgb[1] = 119 / MAX_COLOUR;
					init_9.rgb[2] = 66 / MAX_COLOUR;
					init_9.rotation = 0;
					init_9.params.rect.xlen = cos(PI / 4)*0.3;
					init_9.params.rect.ylen = sin(PI / 4)*0.3;
					init_9.params.rect.zlen = 0.8;
					//init_9.params.rect.isSpoke = TRUE;
					//init_9.params.rect.isSteering = FALSE;
					//init_9.params.rect.normal = FALSE;
					//init_9.isSpoke = TRUE;
					vm.shapes.push_back(init_9);

					/*ptr = new Rectangular(cos(PI / 4)*0.3, sin(PI / 4)*0.3, 0.8);
					ptr->setPosition(1.1, 0.2, -(0.4 + 1.1));
					addShape(ptr);
					ShapeInit init_10;
					init_10.type = RECTANGULAR_PRISM;
					init_10.xyz[0] = 1.1;
					init_10.xyz[1] = 0.2;
					init_10.xyz[2] = -1.5;
					init_10.rgb[0] = 244 / MAX_COLOUR;
					init_10.rgb[1] = 119 / MAX_COLOUR;
					init_10.rgb[2] = 66 / MAX_COLOUR;
					init_10.rotation = 0;
					init_10.params.rect.xlen = cos(PI / 4)*0.3;
					init_10.params.rect.ylen = sin(PI / 4)*0.3;
					init_10.params.rect.zlen = 0.8;
					//init_10.params.rect.is = TRUE;
					//init_10.params.rect.isSteering = FALSE;
					//init_10.params.rect.normal = FALSE;
					//init_10.isSpoke = TRUE;
					vm.shapes.push_back(init_10);*/
					
					// student code goes here
					//
					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// if we're connected, send our vehicle state to the server
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			vs.rotation = vehicle->getRotation();
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// if we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for(unsigned int i = 0; i < msgs.size(); i++ ) {

				RemoteMessage msg = msgs[i];
				//cout << msg.payload << endl;

				switch(msg.type) {
					// new models
					case 'M':
						{
							std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
							for(unsigned int i = 0; i < models.size(); i++) {
								VehicleModel vm = models[i];
								
								// uncomment the line below to create remote vehicles
								//Testing ..... I know what to do now..
								
								
								otherVehicles[vm.remoteID] = new Remote(vm);
								//
								// more student code goes here
								//
							}
							break;
						}

					// vehicle states
					case 'S': 
						{
							std::vector<VehicleState> states = GetVehicleStates(msg.payload);
							for(unsigned int i = 0; i < states.size(); i++) {
								VehicleState vs = states[i];

								
								//std::cout << "id " << vs.remoteID << " Speed is " << vs.speed << std::endl;
								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
								if(iter != otherVehicles.end()) {
									Vehicle * veh = iter->second;
									
									remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
								}
								
							}
							break;
						}

					// goal state
					case 'G':
						{
							goals = GetGoals(msg.payload);
							break;
						}

					// obstacle state
					case 'O':
						{
							std::vector<ObstacleState> obs = GetObstacles(msg.payload);
							for(unsigned int i = 0; i < obs.size(); i++) {
								Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
								ObstacleManager::get()->addObstacle(o);
							}
							break;
						}

					// disconnect list
					case 'D':
						{
							std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
							for(unsigned int i = 0; i < disconnectedIDs.size(); i++) {
								int id = disconnectedIDs[i];
								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
								if(iter != otherVehicles.end()) {
									delete iter->second;
									otherVehicles.erase(iter);
								}
							}
							break;
						}

					// error message
					case 'E':
						{
							cerr << "Server error: " << msg.payload << endl;
							break;
						}

				}
			} 
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// do a simulation step
	if (vehicle != NULL) {
		vehicle->update(speed, steering, elapsedTime);
	}
	for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// keys that will be held down for extended periods of time will be handled
	//   in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// keys that react ocne when pressed rather than need to be held down
	//   can be handles normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;      
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;
	}

};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {  
	KeyManager::get()->specialKeyReleased(keycode);  
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};
void Remote::getVehicleState(VehicleState vs)
{
	cars_states.push_back(vs);
}