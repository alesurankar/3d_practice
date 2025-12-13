#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "CubeScreenTransformer.h"
#include "Cube.h"
#include "Mat.h"

class Object
{
public:
	void Update()
	{
		triangles = cube.GetTriangles();

		rot =
			Mat3::RotationX(theta_x) *
			Mat3::RotationY(theta_y + PI) *
			Mat3::RotationZ(theta_z);

		// transform from model space -> world (/view) space
		for (auto& v : triangles.vertices)
		{
			v *= rot;
			v += { x, y, z };
		}


		// backface culling test (must be done in world (/view) space)
		for (size_t i = 0,
			end = triangles.indices.size() / 3;
			i < end; i++)
		{
			const Vec3& v0 = triangles.vertices[triangles.indices[i * 3]];
			const Vec3& v1 = triangles.vertices[triangles.indices[i * 3 + 1]];
			const Vec3& v2 = triangles.vertices[triangles.indices[i * 3 + 2]];
			triangles.cullFlags[i] = (v1 - v0) % (v2 - v0) * v0 > 0.0f;
		}
		// transform to screen space (includes perspective transform)
		for (auto& v : triangles.vertices)
		{
			cst.Transform(v);
		}
	}

	void Draw(Graphics& gfx) const
	{
		// draw the triangles!
		for (size_t i = 0,
			end = triangles.indices.size() / 3;
			i < end; i++)
		{
			// skip triangles previously determined to be back-facing
			if (!triangles.cullFlags[i])
			{
				gfx.DrawTriangle(
					triangles.vertices[triangles.indices[i * 3]],
					triangles.vertices[triangles.indices[i * 3 + 1]],
					triangles.vertices[triangles.indices[i * 3 + 2]],
					colors[i]);
			}
		}
	}
public:
	Cube cube = Cube(1.0f);
	static constexpr Color colors[12] = {
		Colors::White,
		Colors::Blue,
		Colors::Cyan,
		Colors::Gray,
		Colors::Green,
		Colors::Magenta,
		Colors::LightGray,
		Colors::Red,
		Colors::Yellow,
		Colors::White,
		Colors::Blue,
		Colors::Cyan
	};
	CubeScreenTransformer cst;
	IndexedTriangleList triangles;
	Mat3 rot;
	static constexpr float dTheta = PI;
	float x = 0.0f;
	float y = 0.0f;
	float z = 2.0f;
	float theta_x = 0.0f;
	float theta_y = 0.0f;
	float theta_z = 0.0f;
};