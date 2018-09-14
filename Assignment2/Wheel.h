#pragma once
#include "Cylinder.h"
#include "Rectangular.h"
#include "Vehicle.hpp"

//New wheel class to handle turing wheel..
class Wheel : public Vehicle{
protected:
	double x;
	double y;
	double z;
	double t;
	double r;
	double v;
	double h;
	double angle;

public:
	Wheel(double x_cor,double y_cor,double z_cor,double speed,double time,double radius,double depth,double rotation);
	void draw();


};