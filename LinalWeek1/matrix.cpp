#include "pch.h"
#include "matrix.h"
#include <valarray>
#include <iostream>
#include <numeric>


void matrix::add_vector(const vector vector)
{
	vectors_.push_back(vector);
}

vector matrix::get_vector(const int index) const
{
	return vectors_[index];
}

int matrix::count() const
{
	return vectors_.size();
}

void matrix::clear()
{
	return vectors_.clear();
}

void matrix::multiply(const double x, const double y)
{
	for (auto& vector : vectors_)
	{
		const auto vx = vector.get_x();
		const auto vy = vector.get_y();
		vector.set_x(x * vx + 0 * vy);
		vector.set_y(0 * vx + y * vy);
	}
}

void matrix::multiply(double x, double y, vector origin)
{
	translate(-origin.get_x(), -origin.get_y());
	multiply(x, y);
	translate(origin.get_x(), origin.get_y());
 }

void matrix::multiply(const double scale)
{
	multiply(scale, scale);
}

void matrix::multiply(double scale, vector origin)
{
	multiply(scale, scale, origin);
}

void matrix::translate(double x, double y)
{
	for (auto& vector : vectors_)
	{
		const auto vx = vector.get_x();
		const auto vy = vector.get_y();
		vector.set_x(x + vx);
		vector.set_y(y + vy);
	}
}

void matrix::rotate(double degrees_angle)
{
	const auto radians_theta = degrees_angle * (M_PI / 180.);
	for (auto&& it = vectors_.begin(); it != vectors_.end(); ++it)
	{
		const auto old_x = it->get_x();
		const auto old_y = it->get_y();

		const auto cosinus = std::cos(radians_theta);
		const auto sinus = std::sin(radians_theta);

		const auto x = cosinus * old_x - sinus * old_y;
		const auto y = sinus * old_x + cosinus * old_y;

		it->set_x(x);
		it->set_y(y);
	}
}

vector matrix::get_center()
{
	double x = 0;
	double y = 0;
	for (auto&& vector : vectors_)
	{
		x += vector.get_x();
		y += vector.get_y();
	}
	x = x / vectors_.size();
	y = y / vectors_.size();
	return vector{x, y};
}
