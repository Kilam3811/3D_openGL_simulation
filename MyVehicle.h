#pragma once
#include "Vehicle.hpp"


class MyVehicle : public Vehicle {
public:
	void draw();
	MyVehicle();
	~MyVehicle();
	void for_spin();
	void jud_spin(double X,double Y,double Z);

private:
	double spin;
};
