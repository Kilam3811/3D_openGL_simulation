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
#include "XBoxController.h"
#include <cmath>

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
	//Doing nothing for now..
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

	testing_Draw();
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

//Create instance of xbox controller.
XInputWrapper xinput;
GamePad::XBoxController x_control(&xinput, 2);

//Create global variables that store the infomation we need to trace the ID1 car.
double ID1_steering = 0;
double ID1_speed = 0;
double ID1_x = 0;
double ID1_y = 0;
double ID1_z = 0;
double ID1_rotation = 0;
double My_x = 0;
double My_z = 0;
//Once the trigger == TRUE then start tracing.
bool trigger = FALSE;
void idle() {

	if (x_control.PressedLeftDpad()) {
		Camera::get()->strafeLeft();
	}

	if (x_control.PressedLeftShoulder()) {
		Camera::get()->strafeDown();
	}

	if (x_control.PressedRightDpad()) {
		Camera::get()->strafeRight();
	}

	if (x_control.PressedDownDpad()) {
		Camera::get()->moveBackward();
	}

	if (x_control.PressedUpDpad()) {
		Camera::get()->moveForward();
	}

	if (x_control.PressedRightShoulder()) {
		Camera::get()->strafeUp();
	}
	if (x_control.PressedB()) {
		Camera::get()->togglePursuitMode();
	}
	//Thunmb range
#define MAX_RANGE 32767.0
	speed = 0;
	steering = 0;
	GamePad::Coordinate pt_1 = x_control.RightThumbLocation();
	GamePad::Coordinate pt_2 = x_control.LeftThumbLocation();
	double mag_1 = sqrt(pt_1.GetX()*pt_1.GetX() + pt_1.GetY()*pt_1.GetY());
	double mag_2 = sqrt(pt_2.GetX()*pt_2.GetX() + pt_2.GetY()*pt_2.GetY());

	if (pt_1.GetX() < 0) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * (pt_1.GetX()/MAX_RANGE);
	}

	if (pt_1.GetX() > 0) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS *-1 *(pt_1.GetX() / MAX_RANGE);
	}

	
	if (KeyManager::get()->isAsciiKeyPressed('L')||trigger == TRUE) {
		//A method to trace the car by calculating angle.
		double dx = ID1_x - My_x;
		double dz = ID1_z - My_z;
		double rotation_radian = atan2(dz, dx);
		double rotation_degree = (rotation_radian * 180) / PI;

		if (rotation_degree > PI / 2)rotation_degree -= PI / 2;
		vehicle->setRotation(rotation_degree);

		if (fabs(dx) < 1.5 || fabs(dz) < 1.5) {
			speed = ID1_speed * 0.95;
		}
		else if (ID1_speed < 2.5) {
			speed = 0;
		}
		else {
			speed = ID1_speed;
		}
		steering = ID1_steering;
		trigger = TRUE;
	}
	//If pressed "C" to stop tracing.
	if (KeyManager::get()->isAsciiKeyPressed('C')) {
		trigger = FALSE;
	}
	
	if (pt_2.GetY() > 0) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS * fabs(pt_2.GetY()) / MAX_RANGE;
	}
	if (pt_2.GetY() < 0) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS * fabs(pt_2.GetY()) / MAX_RANGE;
	}
	if (x_control.PressedBack()) {
		exit(0);
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

					//Sending each shapes of my car to the server.
					VehicleModel vm;
					vm.remoteID = 0;
					ShapeInit init;
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
					vm.shapes.push_back(init);


					ShapeInit init_1;
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
					vm.shapes.push_back(init_1);

					ShapeInit init_2;
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
					vm.shapes.push_back(init_2);

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
					vm.shapes.push_back(init_3);

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
					vm.shapes.push_back(init_4);

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
					vm.shapes.push_back(init_5);


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
					vm.shapes.push_back(init_6);

				
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
			My_x = vs.x;
			My_z = vs.z;
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
								//My new class to handle other vehivles.
								//My new constructor which takes VehicleModle as parameters.
								otherVehicles[vm.remoteID] = new Remote(vm);
							}
							break;
						}

					// vehicle states
					case 'S': 
						{
							std::vector<VehicleState> states = GetVehicleStates(msg.payload);
							for(unsigned int i = 0; i < states.size(); i++) {
								VehicleState vs = states[i];
								if (i > 0) {
									//  std::cout << "ID 2 is now at " << "[" << states[1].x << "," << 0 << "," << states[1].z << "]" << std::endl;
								}
								ID1_steering = states[0].steering;
								ID1_speed = states[0].speed;
								ID1_x = states[0].x;
								ID1_z = states[0].z;
								ID1_rotation = states[0].rotation;
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
}

