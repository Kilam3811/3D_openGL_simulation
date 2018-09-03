#pragma once
#include "Vehicle.hpp"
#include "Messages.hpp"

class MyVehicle : public Vehicle {
protected:
	//Some extra variables?
public:
	MyVehicle();
	MyVehicle(VehicleModel *vm , ShapeInit *init);
	void draw();
	void turning_effect();
};