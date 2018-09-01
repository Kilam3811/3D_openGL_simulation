#pragma once
#include "Shape.hpp"

class Trapezoidal : public Shape {
protected:
	double a_length;
	double height;
	double b_length;
	double depth;
	double a_offset;
	double b_offset;
public:
	void setLength(double a_length_,double b_length_, double height_, double depth_,double a_offset_,double b_offset_);
	void draw();
	double get_a_length();
	double get_b_length();
	double get_height();
	double get_depth();
	double get_a_offset();
	double get_b_offset();
};
