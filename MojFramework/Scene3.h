#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Thing.h"
#include "Thing2.h"
#include "Plane.h"
#include "Vec2.h"
#include "Pipeline.h"
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
private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> vRand;
	std::uniform_real_distribution<float> pRand;
	std::uniform_real_distribution<float> zRand;
	std::shared_ptr<ZBuffer> sharedZ; 
	Pipeline<SceneEffect> litPipeline; 
	Pipeline<SolidEffect> unlitPipeline;
	std::vector<std::unique_ptr<Thing2>> objects; 
	std::vector<std::unique_ptr<Thing>> lights; 
	Thing* player = nullptr;
	static constexpr float aspect = Graphics::ScreenWidth / float(Graphics::ScreenHeight);
	static constexpr float nearZ = 1.0f;
	static constexpr float farZ = 200.0f;
	static constexpr float fieldOfView = 70.0f;
	const Mat4 proj = Mat4::ProjectionHFOV(fieldOfView, aspect, nearZ, farZ);
	Vec3 cam_pos = { 0.0f,0.0f,0.0f };
	Vec3 light_pos = { 0.0f,0.0f,0.6f };
	Mat4 view = Mat4::Translation(-cam_pos);
};