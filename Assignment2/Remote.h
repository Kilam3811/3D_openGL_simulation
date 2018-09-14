#pragma once
#include "MyVehicle.h"
#include "Messages.hpp"
#include "Triangular.h"
#include "Rectangular.h"
#include "Cylinder.h"
#include "Trapezoidal.h"
#include "VectorMaths.hpp"


class Remote : public MyVehicle {
protected:
	VehicleModel vm;
	std::vector<Shape *> cars;
public:
	Remote(VehicleModel vm_);
	void draw();
	void draw_rec(double xLength, double yLength, double zLength, double red, double green, double blue, double x_cor, double y_cor, double z_cor, double rotate_angle);
	void draw_tri(double a_len, double b_len, double depth, double theta, double red, double green, double blue, double x_cor, double y_cor, double z_cor, double rotate_angle);
	void draw_tra(double a_len, double b_len, double depth, double height, double offset, double red, double green, double blue, double x_cor, double y_cor, double z_cor, double rotate_angle);
	void draw_cyl(double radius, double depth, double red, double green, double blue, double x_cor, double y_cor, double z_cor, double rotate_angle);
	void add_to_draw_list(Shape*);
	void add_to_shapeInit_list(ShapeInit init);
	bool check_wheel(Cylinder* cyl);
};