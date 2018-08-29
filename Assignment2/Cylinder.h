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

	//Setters
	void setRaius(double r);
	void setheight(double h);
	void setSlices(double slice_);
	void setStacks(double stacks_);

	//Getters
	double getRadius();
	double getHeight();
	double getSlices();
	double getStacks();
};
