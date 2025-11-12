#pragma once
#include "Mat.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <string>
#include "MouseTracker.h"


class Scene
{
public:
	Scene(const std::string& name)
		:
		name(name)
	{}
	virtual void Update(Keyboard& kbd, Mouse& mouse, float dt);
	virtual void Draw() = 0;
	virtual ~Scene() = default;
	const std::string& GetName() const
	{
		return name;
	}
protected:
	std::string name;
	MouseTracker mt;
	// fov
	static constexpr float aspect_ratio = 1.33333f;
	static constexpr float hfov = 95.0f;
	static constexpr float vfov = hfov / aspect_ratio;
	// camera stuff
	static constexpr float htrack = to_rad(hfov) / (float)Graphics::ScreenWidth;
	static constexpr float vtrack = to_rad(vfov) / (float)Graphics::ScreenHeight;
	static constexpr float cam_speed = 1.0f;
	static constexpr float cam_roll_speed = PI;
	Vec3 cam_pos = { 0.0f,0.0f,0.0f };
	Mat4 cam_rot_inv = Mat4::Identity();
	// model stuff
	Vec3 mod_pos = { 0.0f,0.0f,2.0f };
	float theta_x = 0.0f;
	float theta_y = 0.0f;
	float theta_z = 0.0f;
	// light stuff
	Vec4 l_pos = { 0.0f,0.0f,0.6f,1.0f };
	bool lmb_down = false;
	bool rmb_down = false;
	Vei2 mouseHoldPosition = { 0,0 };
	Vei2 mouseClickPosition = { 0,0 };
};