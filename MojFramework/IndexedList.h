#pragma once
#include <vector>
#include "Vec3.h"
#include <utility>
#include <cassert>

template<class T>
class IndexedTriangleList
{
public:
	IndexedTriangleList(std::vector<T> verts_in, std::vector<size_t> indices_in)
		:
		vert(std::move(verts_in)),
		ind(std::move(indices_in))
	{
		assert(vert.size() > 2);
		assert(ind.size() % 3 == 0);
	}
	std::vector<T> vert;
	std::vector<size_t> ind;
};
