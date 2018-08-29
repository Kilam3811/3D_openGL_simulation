#pragma once
#include "Shape.hpp"

class Cylinder : public Shape {
protected:
	double radius;
	double depth;
	double slices;
	double stacks;

public:
	//Draw cylinder
	void draw();

	//Setter
	void set_Dimension(double radius_,double depth_,double slices_,double stacks_);

	//Getters
	double getRadius();
	double getHeight();
	double getSlices();
	double getStacks();
};
