#include "Scene.h"

void Scene::Update(Keyboard& kbd, Mouse& mouse, float dt)
//{
//	float clickCenter = (float)mouseClickPosition.x;
//	float mouseOffset = (float)mouseHoldPosition.x - clickCenter;
//	const float normalizedOffset = mouseOffset / clickCenter;
//	const float rotationAmount = cam_roll_speed * dt * normalizedOffset;
//	// Forward/Backward movement
//	if (kbd.KeyIsPressed('W'))
//	{
//		cam_pos += Vec4{ 0.0f,0.0f,1.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
//	}
//	if (kbd.KeyIsPressed('S'))
//	{
//		cam_pos += Vec4{ 0.0f,0.0f,-1.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
//	}
//	if (lmb_down && rmb_down)
//	{
//		cam_pos += Vec4{ 0.0f,0.0f,1.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
//	}
//
//	// Camera yaw (turn left/right)
//	if (kbd.KeyIsPressed('A'))
//	{
//		cam_pos += Vec4{ -1.0f,0.0f,0.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
//	}
//	if (kbd.KeyIsPressed('D'))
//	{
//		cam_pos += Vec4{ 1.0f,0.0f,0.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
//	}
//
//	// Strafing (left/right movement)
//	if (kbd.KeyIsPressed('Q'))
//	{
//		cam_rot_inv = cam_rot_inv * Mat4::RotationY(cam_roll_speed * dt);
//	}
//	if (kbd.KeyIsPressed('E'))
//	{
//		cam_rot_inv = cam_rot_inv * Mat4::RotationY(-cam_roll_speed * dt);
//	}
//
//	// Vertical movement (up/down)
//	if (kbd.KeyIsPressed(VK_SPACE))
//	{
//		cam_pos += Vec4{ 0.0f,1.0f,0.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
//	}
//	if (kbd.KeyIsPressed(VK_SHIFT))
//	{
//		cam_pos += Vec4{ 0.0f,-1.0f,0.0f,0.0f } *!cam_rot_inv * cam_speed * dt;
//	}
//	while (!mouse.IsEmpty())
//	{
//		const auto e = mouse.Read();
//		mouseHoldPosition = e.GetPos();
//		switch (e.GetType())
//		{
//		case Mouse::Event::Type::LPress:
//			mt.Engage(mouseHoldPosition);
//			lmb_down = true;
//			break;
//
//		case Mouse::Event::Type::LRelease:
//			mt.Release();
//			lmb_down = false;
//			break;
//
//		case Mouse::Event::Type::RPress:
//			mt.Engage(mouseHoldPosition);
//			if (!rmb_down)
//			{
//				mouseClickPosition = e.GetPos();
//			}
//			rmb_down = true;
//			break;
//
//		case Mouse::Event::Type::RRelease:
//			mt.Release();
//			rmb_down = false;
//			break;
//
//		case Mouse::Event::Type::Move:
//		{
//			if (rmb_down)
//			{
//				const auto delta = mt.Move(mouseHoldPosition);
//				cam_rot_inv = cam_rot_inv
//					* Mat4::RotationY((float)-delta.x * htrack)
//					* Mat4::RotationX((float)-delta.y * vtrack);
//			}
//			break;
//		}
//
//		case Mouse::Event::Type::WheelUp:
//			// Zoom in
//			cam_pos += Vec4{ 0.0f, 0.0f, 1.0f, 0.0f } *!cam_rot_inv * cam_speed * 0.2f;
//			break;
//
//		case Mouse::Event::Type::WheelDown:
//			// Zoom out
//			cam_pos += Vec4{ 0.0f, 0.0f, -1.0f, 0.0f } *!cam_rot_inv * cam_speed * 0.2f;
//			break;
//		}
//	}
//}


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
