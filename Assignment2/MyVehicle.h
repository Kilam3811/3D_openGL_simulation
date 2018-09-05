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
	bool check_wheel(Cylinder * cyl);
	//void turning_effect(Shape* shape_);
};