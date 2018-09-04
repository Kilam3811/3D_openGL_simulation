#pragma once
#include "Vehicle.hpp"
#include "Messages.hpp"

class MyVehicle : public Vehicle {
protected:
	//Some extra variables?
public:
	MyVehicle();
	void draw();
	//void turning_effect(Shape* shape_);
};