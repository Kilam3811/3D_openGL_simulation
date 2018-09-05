#pragma once
#include "Shape.hpp"

class Cylinder : public Shape {
protected:
	double radius;
	double depth;
	double slices;
	double stacks;

public:
	Cylinder(double radius_, double depth_, double slices_, double stacks_);
	//Draw cylinder
	void draw();

	void Rolling();
	void draw_rolling();
	//Setter
	void set_Dimension(double radius_,double depth_,double slices_,double stacks_);

	//Getters
	double getRadius();
	double getHeight();
	double getSlices();
	double getStacks();
};
