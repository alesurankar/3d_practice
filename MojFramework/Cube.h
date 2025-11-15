#pragma once
#include "Vec3.h"
#include "Vec2.h"
#include <vector>
#include "IndexedLineList.h"

class Cube
{
public:
	Cube(float size)
	{
		const float side = size / 2.0f;
		vert3.emplace_back(-side, -side, -side);
		vert3.emplace_back(side, -side, -side);
		vert3.emplace_back(-side, side, -side);
		vert3.emplace_back(side, side, -side);
		vert3.emplace_back(-side, -side, side);
		vert3.emplace_back(side, -side, side);
		vert3.emplace_back(-side, side, side);
		vert3.emplace_back(side, side, side);
	}
	IndexedLineList GetLines() const
	{
		return{
			vert3,{
			0,1,  1,3,  3,2,  2,0,
			0,4,  1,5,	3,7,  2,6,
			4,5,  5,7,	7,6,  6,4 }
		};
	}
private:
	std::vector<Vec3> vert3;
};


class Rct
{
public:
	Rct(float size)
	{
		const float side = size / 2.0f;
		vert2.emplace_back(-side, -side);
		vert2.emplace_back(side, -side);
		vert2.emplace_back(-side, side);
		vert2.emplace_back(side, side);
	}
	IndexedLineList2 GetLines() const
	{
		return{
			vert2,{
			0,1,  1,3,
			0,2,  2,3 }
		};
	}
private:
	std::vector<Vec2> vert2;
};

