#pragma once
#include "Vec3.h"
#include "Mat.h"
#include "IndexedList.h"


class Sphere
{
public:
	template<class V>
	static IndexedTriangleList<V> GetPlain(float radius = 1.0f, int latDiv = 12, int longDiv = 24)
	{
		const Vec3 base = { 0.0f,0.0f,radius };
		const float lattitudeAngle = PI / latDiv;
		const float longitudeAngle = 2.0f * PI / longDiv;

		std::vector<V> vert;
		for (int iLat = 1; iLat < latDiv; iLat++)
		{
			const auto latBase = base * Mat3::RotationX(lattitudeAngle * iLat);
			for (int iLong = 0; iLong < longDiv; iLong++)
			{
				vert.emplace_back();
				vert.back().pos = latBase * Mat3::RotationZ(longitudeAngle * iLong);
			}
		}

		// add the cap vertices
		const auto iNorthPole = vert.size();
		vert.emplace_back();
		vert.back().pos = base;
		const auto iSouthPole = vert.size();
		vert.emplace_back();
		vert.back().pos = -base;

		const auto calcIdx = [latDiv, longDiv](int iLat, int iLong)
			{ return iLat * longDiv + iLong; };
		std::vector<size_t> ind;
		for (int iLat = 0; iLat < latDiv - 2; iLat++)
		{
			for (int iLong = 0; iLong < longDiv - 1; iLong++)
			{
				ind.push_back(calcIdx(iLat, iLong));
				ind.push_back(calcIdx(iLat + 1, iLong));
				ind.push_back(calcIdx(iLat, iLong + 1));
				ind.push_back(calcIdx(iLat, iLong + 1));
				ind.push_back(calcIdx(iLat + 1, iLong));
				ind.push_back(calcIdx(iLat + 1, iLong + 1));
			}
			// wrap band
			ind.push_back(calcIdx(iLat, longDiv - 1));
			ind.push_back(calcIdx(iLat + 1, longDiv - 1));
			ind.push_back(calcIdx(iLat, 0));
			ind.push_back(calcIdx(iLat, 0));
			ind.push_back(calcIdx(iLat + 1, longDiv - 1));
			ind.push_back(calcIdx(iLat + 1, 0));
		}

		// cap fans
		for (int iLong = 0; iLong < longDiv - 1; iLong++)
		{
			// north
			ind.push_back(iNorthPole);
			ind.push_back(calcIdx(0, iLong));
			ind.push_back(calcIdx(0, iLong + 1));
			// south
			ind.push_back(calcIdx(latDiv - 2, iLong + 1));
			ind.push_back(calcIdx(latDiv - 2, iLong));
			ind.push_back(iSouthPole);
		}
		// wrap triangles
		// north
		ind.push_back(iNorthPole);
		ind.push_back(calcIdx(0, longDiv - 1));
		ind.push_back(calcIdx(0, 0));
		// south
		ind.push_back(calcIdx(latDiv - 2, 0));
		ind.push_back(calcIdx(latDiv - 2, longDiv - 1));
		ind.push_back(iSouthPole);


		return{ std::move(vert),std::move(ind) };
	}
	template<class V>
	static IndexedTriangleList<V> GetPlainNormals(float radius = 1.0f, int latDiv = 12, int longDiv = 24)
	{
		auto sphere = GetPlain<V>(radius, latDiv, longDiv);
		for (auto& v : sphere.vert)
		{
			v.n = v.pos.GetNormalized();
		}
		return sphere;
	}
};