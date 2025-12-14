#pragma once
#include "CubeMesh.h"
#include "Mat.h"
#include "MyPipeline.h"
#include <memory>


struct SimpleObject
{
	CubeMesh cube;
	Vec3 translation = { 0.0f, 0.0f, 0.0f };
	Mat3 rotation = Mat3::Identity();

	SimpleObject(float size) : cube(size) {}
};


class MyScene
{
public:
	MyScene(Graphics& gfx)
		:
		pipeline(gfx)
	{
		triStatic = std::make_unique<SimpleObject>(1.0f);
		triMovable = std::make_unique<SimpleObject>(1.0f);

		triStatic->translation = { 0.0f, 0.0f, 3.0f };
		triMovable->translation = { 0.0f, 0.0f, 3.0f };
	}
	void Update(Keyboard& kbd, Mouse& mouse, float dt)
	{
		float speed = 1.0f * dt;
		if (kbd.KeyIsPressed(VK_SPACE)) {
			speed = 3.0f * dt;
		}
		if (kbd.KeyIsPressed('W')) {
			triMovable->translation.y += speed;
		}
		if (kbd.KeyIsPressed('S')) {
			triMovable->translation.y -= speed;
		}
		if (kbd.KeyIsPressed('A')) {
			triMovable->translation.x -= speed;
		}
		if (kbd.KeyIsPressed('D')) {
			triMovable->translation.x += speed;
		}
//		if (kbd.KeyIsPressed('Q')) {
//			obj->Rotate(0, 0, obj->dTheta * speed);
//			obj->theta_z = wrap_angle(obj->theta_z + obj->dTheta * speed);
//		}
//		if (kbd.KeyIsPressed('E')) {
//			obj->Rotate(0, 0, obj->dTheta *  (-speed));
//			obj->theta_z = wrap_angle(obj->theta_z - obj->dTheta * speed);
//		}
//		if (kbd.KeyIsPressed('R')) {
//			obj->Rotate(obj->dTheta * speed, 0, 0);
//			obj->theta_x = wrap_angle(obj->theta_x + obj->dTheta * speed);
//		}
//		if (kbd.KeyIsPressed('F')) {
//			obj->Rotate(obj->dTheta * (-speed), 0, 0);
//			obj->theta_x = wrap_angle(obj->theta_x - obj->dTheta * speed);
//		}
//		if (kbd.KeyIsPressed('T')) {
//			obj->Rotate(0, obj->dTheta * speed, 0);
//			obj->theta_y = wrap_angle(obj->theta_y + obj->dTheta * speed);
//		}
//		if (kbd.KeyIsPressed('G')) {
//			obj->Rotate(0, obj->dTheta * (-speed), 0);
//			obj->theta_y = wrap_angle(obj->theta_y - obj->dTheta * speed);
//		}
		while (!mouse.IsEmpty())
		{
			Mouse::Event e = mouse.Read();

			switch (e.GetType())
			{
			case Mouse::Event::Type::WheelUp:
				triMovable->translation.z -= (3 * speed);
				break;

			case Mouse::Event::Type::WheelDown:
				triMovable->translation.z += (3 * speed);
				break;
			}
		}
	}
	void Draw()
	{
		pipeline.BindRotation(triStatic->rotation);
		pipeline.BindTranslation(triStatic->translation);
		pipeline.Draw(triStatic->cube.GetTriangles());

		pipeline.BindRotation(triMovable->rotation);
		pipeline.BindTranslation(triMovable->translation);
		pipeline.Draw(triMovable->cube.GetTriangles());
	}
private:
	MyPipeline pipeline;
	std::unique_ptr<SimpleObject> triStatic;
	std::unique_ptr<SimpleObject> triMovable;
};