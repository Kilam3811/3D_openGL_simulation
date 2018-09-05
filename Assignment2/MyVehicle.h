#pragma once
#include "Vehicle.hpp"
#include "Cylinder.h"
#include "Messages.hpp"

class MyVehicle : public Vehicle {
protected:
	//Some extra variables?
	std::vector<ShapeInit> cars_shapeInit;
public:
	MyVehicle();
	void draw();
	bool check_front_wheel(Cylinder * cyl);
};