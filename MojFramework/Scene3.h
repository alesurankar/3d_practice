#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Thing.h"
#include "Thing2.h"
#include "Bullet.h"
#include "Vec2.h"
#include "Pipeline.h"
#include <memory>

class Scene3
{
public:
	Scene3(Graphics& gfx);
	void Update(const Keyboard& kbd, Mouse& mouse, float dt);
	void Draw();
private:
	void BindAndDraw(const Thing2& obj);
private:
	Pipeline<GeometryFlatEffect> pipeline;
	std::vector<std::unique_ptr<Thing2>> objects;
	//std::vector<std::unique_ptr<Bullet>> bullets;
	static constexpr float aspect = Graphics::ScreenWidth / float(Graphics::ScreenHeight);
	static constexpr float nearZ = 1.0f;
	static constexpr float farZ = 200.0f;
	static constexpr float fieldOfView = 60.0f;
};