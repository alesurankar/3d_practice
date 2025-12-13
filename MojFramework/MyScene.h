#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Cube.h"
#include "CubeScreenTransformer.h"
#include "Mat.h"

class MyScene
{
public:
	MyScene() = default;
	void Update(Keyboard& kbd, Mouse& mouse, float dt)
	{
		float speed = 1.0f * dt;
		if (kbd.KeyIsPressed(VK_SPACE)) {
			speed = 3.0f * dt;
		}
		if (kbd.KeyIsPressed('W')) {
			y += speed;
		}
		if (kbd.KeyIsPressed('S')) {
			y -= speed;
		}
		if (kbd.KeyIsPressed('A')) {
			x -= speed;
		}
		if (kbd.KeyIsPressed('D')) {
			x += speed;
		}
		if (kbd.KeyIsPressed('Q')) {
			theta_z = wrap_angle(theta_z + dTheta * speed);
		}
		if (kbd.KeyIsPressed('E')) {
			theta_z = wrap_angle(theta_z - dTheta * speed);
		}
		if (kbd.KeyIsPressed('R')) {
			theta_x = wrap_angle(theta_x + dTheta * speed);
		}
		if (kbd.KeyIsPressed('F')) {
			theta_x = wrap_angle(theta_x - dTheta * speed);
		}
		if (kbd.KeyIsPressed('T')) {
			theta_y = wrap_angle(theta_y + dTheta * speed);
		}
		if (kbd.KeyIsPressed('G')) {
			theta_y = wrap_angle(theta_y - dTheta * speed);
		}
		while (!mouse.IsEmpty())
		{
			Mouse::Event e = mouse.Read();

			switch (e.GetType())
			{
			case Mouse::Event::Type::WheelUp:
				z -= (3 * speed);
				break;

			case Mouse::Event::Type::WheelDown:
				z += (3 * speed);
				break;
			}
		}
	}
	void Draw(Graphics& gfx) const
	{
		// generate indexed triangle list
		auto triangles = cube.GetTriangles();
		// generate rotation matrix from euler angles
		const Mat3 rot =
			Mat3::RotationX(theta_x) *
			Mat3::RotationY(theta_y) *
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
private:
	CubeScreenTransformer cst;
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
	static constexpr float dTheta = PI;
	float x = 0.0f;
	float y = 0.0f;
	float z = 2.0f;
	float theta_x = 0.0f;
	float theta_y = 0.0f;
	float theta_z = 0.0f;
};