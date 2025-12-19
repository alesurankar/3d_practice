#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "TestObject.h"
#include "Vec2.h"
#include "Pipeline.h"
#include <memory>
#include <random>

class Scene
{
public:
	Scene(Graphics& gfx);
	void Update(const Keyboard& kbd, Mouse& mouse, float dt);
	void Draw();
private:
	void CheckCollisions();
	void BindAndDraw(const TestObject& obj);
private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> vRand;
	std::uniform_real_distribution<float> pRand;
	std::uniform_real_distribution<float> zRand;
	Pipeline<TextureEffect> pipeline;
	std::vector<std::unique_ptr<TestObject>> objects;
	TestObject* player = nullptr;
};