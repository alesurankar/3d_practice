#pragma once

#include <vector>
#include "Vec3.h"
#include "Vec2.h"

struct IndexedLineList
{
	std::vector<Vec3> vertices;
	std::vector<size_t> indices;
};

struct IndexedLineList2
{
	std::vector<Vec2> vert2;
	std::vector<size_t> ind2;
};