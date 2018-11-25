#include "pch.h"
#include "vector.h"
#include <iostream>


vector::vector(const double x, const double y): x_(x), y_(y)
{
}

double vector::get_x() const
{
	return x_;
}

double vector::get_y() const
{
	return y_;
}

void vector::set_x(double x)
{
	x_ = x;
}

void vector::set_y(double y)
{
	y_ = y;
}

void vector::multiply_by_scalar(const double scalar)
{
	x_ = scalar * x_;
	y_ = scalar * y_;
}

void vector::add_vector(vector vector)
{
	x_ = x_ + vector.get_x();
	y_ = y_ + vector.get_y();
}

void vector::subtract_vector(vector vector)
{
	x_ = x_ - vector.get_x();
	y_ = y_ - vector.get_y();
}

std::string vector::get_notation() const
{
	return std::string("[") + std::to_string(get_x()) + std::string(",") + std::to_string(get_y()) + std::string("]");
}

double vector::get_length() const
{
	return sqrt(x_ * x_ + y_ * y_);
}
