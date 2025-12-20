//#pragma once
//#include "Keyboard.h"
//#include "Mouse.h"
//#include "Graphics.h"
//#include "Thing.h"
//#include "Bullet.h"
//#include "Vec2.h"
//#include "Pipeline.h"
//#include <memory>
//#include <random>
//
//class Scene2
//{
//public:
//	Scene2(Graphics& gfx);
//	void Update(const Keyboard& kbd, Mouse& mouse, float dt);
//	void Draw();
//private:
//	void CheckCollisions();
//	void CheckDestroyed();
//	void BindAndDraw(const Thing& obj);
//	Vec3 GetClickChords(const Mouse& mouse);
//private:
//	Graphics& gfx;
//	std::random_device rd;
//	std::mt19937 rng;
//	std::uniform_real_distribution<float> vRand;
//	std::uniform_real_distribution<float> pRand;
//	std::uniform_real_distribution<float> zRand;
//	Pipeline<TextureLightEffect> pipeline;
//	std::vector<std::unique_ptr<Thing>> objects;
//	std::vector<std::unique_ptr<Bullet>> bullets;
//	static constexpr float aspect = Graphics::ScreenWidth / float(Graphics::ScreenHeight);
//	static constexpr float nearZ = 1.0f;
//	static constexpr float farZ = 200.0f;
//	static constexpr float fieldOfView = 60.0f;
//};