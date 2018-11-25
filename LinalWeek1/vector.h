#pragma once
#include <string>

class vector
{
public:
	vector(double x, double y);
	~vector() = default;
	double get_x() const;
	double get_y() const;
	void set_x(double x);
	void set_y(double y);
	void multiply_by_scalar(double scalar);
	void add_vector(vector vector);
	void subtract_vector(vector vector);
	std::string  get_notation() const;
	double get_length() const;

private:
	double x_;
	double y_;
};

