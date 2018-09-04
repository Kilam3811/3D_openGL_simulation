#pragma once
#include "Shape.hpp"

class Trapezoidal : public Shape {
protected:
	double Len;
	double Wid;
	double Hig;
	double offset1;
	double offset2;
public:
	void setDimension(double L, double W, double H, double OF1, double OF2);
	void draw();
	/*double get_a_length();
	double get_b_length();
	double get_height();
	double get_depth();
	double get_a_offset();
	double get_b_offset();*/
};
