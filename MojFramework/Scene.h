#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Thing1.h"
#include "Thing2.h"
#include "Thing3.h"
#include "Plane.h"
#include "Vec2.h"
#include "Pipeline.h"
#include "MouseTracker.h"
#include "RandomNumber.h"
#include <memory>

class Scene
{
public:
	Scene(Graphics& gfx);
	void Update(const Keyboard& kbd, Mouse& mouse, float dt);
	void Draw();
private:
	void BindAndDrawLights(const Thing1& obj);
	void BindAndDrawObjects(const Thing2& obj);
	void BindAndDrawTexture(const Thing3& obj);
private:
	RandomNumber rn;
	ZBuffer pZb;
	Pipeline<Thing1::Effect> unlitPipeline;
	Pipeline<Thing2::Effect> litPipeline;
	Pipeline<Thing3::Effect> texPipeline;
	MouseTracker mt;
	std::vector<std::unique_ptr<Thing1>> lights;
	std::vector<std::unique_ptr<Thing2>> objects; 
	std::vector<std::unique_ptr<Thing3>> textures; 
	Thing1* light = nullptr;
	static constexpr float aspect_ratio = Graphics::ScreenWidth / float(Graphics::ScreenHeight);
	static constexpr float nearZ = 1.0f;
	static constexpr float farZ = 200.0f; 
	static constexpr float hfov = 70.0f;
	static constexpr float vfov = hfov / aspect_ratio;
	const Mat4 proj = Mat4::ProjectionHFOV(hfov, aspect_ratio, nearZ, farZ);
	static constexpr float htrack = to_rad(hfov) / (float)Graphics::ScreenWidth;
	static constexpr float vtrack = to_rad(vfov) / (float)Graphics::ScreenHeight;
	Vec3 cam_pos = { 0.0f,0.0f,0.0f };
	Mat4 cam_rot = Mat4::Identity();
	Vec4 light_pos;
	Mat4 view = Mat4::Translation(-cam_pos);
};