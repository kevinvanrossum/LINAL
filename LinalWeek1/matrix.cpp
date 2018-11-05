#include "pch.h"
#include "matrix.h"


void matrix::add_vector(vector vector)
{
	vectors_.push_back(vector);
}

vector matrix::get_vector(int index) const
{
	return vectors_[index];
}

int matrix::get_vertex_count() const
{
	return vectors_.size();
}

void matrix::clear()
{
	return vectors_.clear();
}

