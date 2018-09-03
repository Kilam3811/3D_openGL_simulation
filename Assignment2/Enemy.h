#pragma once
#include "MyVehicle.h"
#include "Messages.hpp"
#include "Triangular.h"
#include "Rectangular.h"
#include "Cylinder.h"
#include "Trapezoidal.h"
#include "VectorMaths.hpp"


class Enemy : public MyVehicle {
protected:
	VehicleModel vm;

public:
	Enemy(VehicleModel vm_);
	void draw();
	void draw_rec(double xLength,double yLength,double zLength,double red,double green,double blue,double x_cor,double y_cor,double z_cor,double rotate_angle);
	void draw_tri(double a_len,double b_len,double depth,double theta,double red,double green,double blue,double x_cor,double y_cor,double z_cor,double rotate_angle);
	void draw_tra(double a_len,double b_len,double depth,double height,double offset,double red,double green,double blue,double x_cor,double y_cor,double z_cor,double rotate_angle);
	void draw_cyl(double radius,double depth,double red,double green,double blue,double x_cor,double y_cor,double z_cor,double rotate_angle);
};