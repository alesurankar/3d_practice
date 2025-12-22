#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Thing.h"
#include "Thing2.h"
#include "Thing3.h"
#include "Plane.h"
#include "Vec2.h"
#include "Pipeline.h"
#include "MouseTracker.h"
#include <memory>
#include <random>

class Scene3
{
public:
	Scene3(Graphics& gfx);
	void Update(const Keyboard& kbd, Mouse& mouse, float dt);
	void Draw();
private:
	void BindAndDrawObjects(const Thing2& obj);
	void BindAndDrawLights(const Thing& obj);
	void BindAndDrawTexture(const Thing3& obj);
private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> vRand;
	std::uniform_real_distribution<float> pRand;
	std::uniform_real_distribution<float> zRand;
	std::shared_ptr<ZBuffer> pZb;
	Pipeline<SpecularPhongPointEffect> litPipeline;
	Pipeline<SolidEffect> unlitPipeline;
	Pipeline<VertexLightTexturedEffect> texPipeline;
	MouseTracker mt;
	std::vector<std::unique_ptr<Thing2>> objects; 
	std::vector<std::unique_ptr<Thing>> lights; 
	std::vector<std::unique_ptr<Thing3>> textures; 
	Thing* light = nullptr;
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
	Vec3 light_pos = { 0.0f,0.0f,0.6f };
	Mat4 view = Mat4::Translation(-cam_pos);
};