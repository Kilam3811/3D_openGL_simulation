#pragma once
#include "Vehicle.hpp"
#include "Messages.hpp"

class MyVehicle : public Vehicle {
protected:
	//Some extra variables?
public:
	MyVehicle();
	void setUp_info();
	void draw();
	void turning_effect();
};