#include "pch.h"
#include "vector.h"
#include <iostream>


vector::vector(const int x, const int y): x_(x), y_(y)
{
}

int vector::get_x() const
{
	return x_;
}

int vector::get_y() const
{
	return y_;
}

void vector::multiply_by_scalar(const int scalar)
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

int vector::get_length() const
{
	return sqrt(x_ * x_ + y_ * y_);
}
