#pragma once
#include "Vehicle.hpp"
#include "Cylinder.h"
#include "Messages.hpp"

class MyVehicle : public Vehicle {
protected:
	//Some extra variables?
	std::vector<ShapeInit> cars_shapeInit;

	double x_ID1;
	double y_ID1;
	double z_ID1;
public:
	MyVehicle();
	void draw();
	bool check_front_wheel(Cylinder * cyl);
	void setRemote(double x, double y ,double z);
};