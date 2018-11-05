#pragma once
#include <string>

class vector
{
public:
	vector(int x, int y);
	~vector() = default;
	int get_x() const;
	int get_y() const;
	void multiply_by_scalar(int scalar);
	void add_vector(vector vector);
	void subtract_vector(vector vector);
	std::string  get_notation() const;
	int get_length() const;

private:
	int x_;
	int y_;
};

