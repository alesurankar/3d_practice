#pragma once
#include "Object.h"
#include <memory>

class MyScene
{
public:
	MyScene()
	{
		obj = std::make_unique<Object>();
	}
	void Update(Keyboard& kbd, Mouse& mouse, float dt)
	{
		obj->Update();
		float speed = 1.0f * dt;
		if (kbd.KeyIsPressed(VK_SPACE)) {
			speed = 3.0f * dt;
		}
		if (kbd.KeyIsPressed('W')) {
			obj->y += speed;
		}
		if (kbd.KeyIsPressed('S')) {
			obj->y -= speed;
		}
		if (kbd.KeyIsPressed('A')) {
			obj->x -= speed;
		}
		if (kbd.KeyIsPressed('D')) {
			obj->x += speed;
		}
		if (kbd.KeyIsPressed('Q')) {
			obj->theta_z = wrap_angle(obj->theta_z + obj->dTheta * speed);
		}
		if (kbd.KeyIsPressed('E')) {
			obj->theta_z = wrap_angle(obj->theta_z - obj->dTheta * speed);
		}
		if (kbd.KeyIsPressed('R')) {
			obj->theta_x = wrap_angle(obj->theta_x + obj->dTheta * speed);
		}
		if (kbd.KeyIsPressed('F')) {
			obj->theta_x = wrap_angle(obj->theta_x - obj->dTheta * speed);
		}
		if (kbd.KeyIsPressed('T')) {
			obj->theta_y = wrap_angle(obj->theta_y + obj->dTheta * speed);
		}
		if (kbd.KeyIsPressed('G')) {
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
	}
private:
	std::unique_ptr<Object> obj;
};