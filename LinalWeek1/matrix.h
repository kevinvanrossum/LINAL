#pragma once
#include <vector>
#include "vector.h"

class matrix
{
public:
	void add_vector(vector vector);
	vector get_vector(int index) const;
	int get_vertex_count() const;
	void clear();
private:
	std::vector<vector> vectors_;
};
