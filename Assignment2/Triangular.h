#pragma once
#include "Shape.hpp"
#define PI 3.14159265359
class Triangular : public Shape {
protected:
	double a_length;
	double b_length;
	double depth;
	double theta;
public:
	void draw();
	//Setters
	void setTheta(double angle);
	void setX_length(double x_length);
	void setY_length(double y_length);
	void setZ_length(double z_length);
	
	//Getters
	double getTheta();
	double getX_length();
	double getY_length();
	double getZ_length();

	//Normalization
	double getNormal_X_Cor();
	double getNormal_Y_Cor();

};