#pragma once
#include "Shape.hpp"

class Trapezoidal : public Shape {
protected:
	double a_length;
	double height;
	double b_length;
	double depth;
public:
	void setLength(double a_length_,double b_length_, double height_, double depth_);
	void draw();
	double get_a_length();
	double get_b_length();
	double get_height();
	double get_depth();
};
