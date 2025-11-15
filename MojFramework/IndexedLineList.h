#pragma once

#include <vector>
#include "Vec3.h"
#include "Vec2.h"

struct IndexedLineList
{
	std::vector<Vec3> vertices;
	std::vector<size_t> indices;
};