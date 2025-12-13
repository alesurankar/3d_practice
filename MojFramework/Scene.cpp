#include "Scene.h"

void Scene::Update(Keyboard& kbd, Mouse& mouse, float dt)
{
	if (kbd.KeyIsPressed('W'))
	{
		cam_pos += Vec4{ 0.0f,0.0f,1.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
	}
	if (kbd.KeyIsPressed('A'))
	{
		cam_pos += Vec4{ -1.0f,0.0f,0.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
	}
	if (kbd.KeyIsPressed('S'))
	{
		cam_pos += Vec4{ 0.0f,0.0f,-1.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
	}
	if (kbd.KeyIsPressed('D'))
	{
		cam_pos += Vec4{ 1.0f,0.0f,0.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
	}
	if (kbd.KeyIsPressed('C'))
	{
		cam_pos += Vec4{ 0.0f,1.0f,0.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
	}
	if (kbd.KeyIsPressed('Z'))
	{
		cam_pos += Vec4{ 0.0f,-1.0f,0.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
	}
	if (kbd.KeyIsPressed('Q'))
	{
		cam_rot_inv = cam_rot_inv * Mat4::RotationZ(cam_roll_speed * dt);
	}
	if (kbd.KeyIsPressed('E'))
	{
		cam_rot_inv = cam_rot_inv * Mat4::RotationZ(-cam_roll_speed * dt);
	}

	while (!mouse.IsEmpty())
	{
		const auto e = mouse.Read();
		switch (e.GetType())
		{
		case Mouse::Event::Type::LPress:
			mt.Engage(e.GetPos());
			break;
		case Mouse::Event::Type::LRelease:
			mt.Release();
			break;
		case Mouse::Event::Type::Move:
			if (mt.Engaged())
			{
				const auto delta = mt.Move(e.GetPos());
				cam_rot_inv = cam_rot_inv
					* Mat4::RotationY((float)-delta.x * htrack)
					* Mat4::RotationX((float)-delta.y * vtrack);
			}
			break;
		}
	}
}
