#pragma once
#include "Shape.hpp"
class Rectangular : public Shape {
	protected:
		double x_length;
		double y_length;
		double z_length;
	public:
		void setLength(double x_,double y_,double z_);
		void draw();
		double get_x_length();
		double get_y_length();
		double get_z_length();


};