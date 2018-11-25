#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "vector.h"

class matrix
{
public:
	void add_vector(vector vector);
	vector get_vector(int index) const;
	int count() const;
	void clear();
	void multiply(double x, double y);
	void multiply(double x, double y, vector origin);
	void multiply(double scale);
	void multiply(double scale, vector origin);
	void translate(double x, double y);
	void rotate(double degrees_angle);
	vector get_center();
private:
	std::vector<vector> vectors_;
};
