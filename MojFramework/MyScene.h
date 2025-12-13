#pragma once
#include "Object.h"
#include <memory>

class MyScene
{
public:
	MyScene()
	{
		obj = std::make_unique<Object>();
		obj1 = std::make_unique<Object>();
	}
	void Update(Keyboard& kbd, Mouse& mouse, float dt)
	{
		obj->Update();
		obj1->Update();

		float speed = 1.0f * dt;
		if (kbd.KeyIsPressed(VK_SPACE)) {
			speed = 3.0f * dt;
		}
		if (kbd.KeyIsPressed('W')) {
			obj->Move(0, speed, 0);
		}
		if (kbd.KeyIsPressed('S')) {
			obj->Move(0, -speed, 0);
		}
		if (kbd.KeyIsPressed('A')) {
			obj->Move(-speed, 0, 0);
		}
		if (kbd.KeyIsPressed('D')) {
			obj->Move(speed, 0, 0);
		}
		if (kbd.KeyIsPressed('Q')) {
			obj->Rotate(0, 0, obj->dTheta * speed);
			obj->theta_z = wrap_angle(obj->theta_z + obj->dTheta * speed);
		}
		if (kbd.KeyIsPressed('E')) {
			obj->Rotate(0, 0, obj->dTheta *  (-speed));
			obj->theta_z = wrap_angle(obj->theta_z - obj->dTheta * speed);
		}
		if (kbd.KeyIsPressed('R')) {
			obj->Rotate(obj->dTheta * speed, 0, 0);
			obj->theta_x = wrap_angle(obj->theta_x + obj->dTheta * speed);
		}
		if (kbd.KeyIsPressed('F')) {
			obj->Rotate(obj->dTheta * (-speed), 0, 0);
			obj->theta_x = wrap_angle(obj->theta_x - obj->dTheta * speed);
		}
		if (kbd.KeyIsPressed('T')) {
			obj->Rotate(0, obj->dTheta * speed, 0);
			obj->theta_y = wrap_angle(obj->theta_y + obj->dTheta * speed);
		}
		if (kbd.KeyIsPressed('G')) {
			obj->Rotate(0, obj->dTheta * (-speed), 0);
			obj->theta_y = wrap_angle(obj->theta_y - obj->dTheta * speed);
		}
		while (!mouse.IsEmpty())
		{
			Mouse::Event e = mouse.Read();

			switch (e.GetType())
			{
			case Mouse::Event::Type::WheelUp:
				obj->z -= (3 * speed);
				break;

			case Mouse::Event::Type::WheelDown:
				obj->z += (3 * speed);
				break;
			}
		}
	}
	void Draw(Graphics& gfx) const
	{
		obj->Draw(gfx);
		obj1->Draw(gfx);
	}
private:
	std::unique_ptr<Object> obj;
	std::unique_ptr<Object> obj1;
};