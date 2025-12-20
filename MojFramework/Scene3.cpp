#include "Scene3.h"

Scene3::Scene3(Graphics& gfx)
	:
	pipeline(gfx)
{
	//objects.emplace_back(std::make_unique<Thing>(gfx, Vec3(0.0f, 0.0f, 0.0f), L"Images\\stonewall.jpg", 4.0f));
	objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 0.0f, 0.0f), 4.0f));
	for (auto& obj : objects) {
		obj->SetVelocity(2.0f, -3.0f, 4.0f);
		obj->SetTorque(0.3f, 0.3f, 0.3f);
	}
}


void Scene3::Update(const Keyboard& kbd, Mouse& mouse, float dt)
{
	for (auto& obj : objects) {
		obj->Move(dt);
		obj->Rotate(dt);
	}
}

void Scene3::Draw()
{
	pipeline.BeginFrame();
	for (auto& obj : objects) {
		BindAndDraw(*obj);
	}
}

void Scene3::BindAndDraw(const Thing2& obj)
{
	//pipeline.effect.ps.BindTexture(obj.GetTexture());
	pipeline.effect.gs.BindColors(
		{ Colors::Red,Colors::Green,Colors::Blue,Colors::Magenta,Colors::Yellow,Colors::Cyan }
	);
	
	//const auto proj = Mat4::ProjectionHFOV(fieldOfView, aspect, nearZ, farZ);
	//const Mat4 world =
	//	Mat4::RotationX(obj.GetOrnt().x) *
	//	Mat4::RotationY(obj.GetOrnt().y) *
	//	Mat4::RotationZ(obj.GetOrnt().z) *
	//	Mat4::Translation(obj.GetPos().x, obj.GetPos().y, obj.GetPos().z);
	//
	//pipeline.effect.vs.BindWorld(world);
	//pipeline.effect.vs.BindProjection(proj);


	
	const Mat3 rot =
		Mat3::RotationX(obj.GetOrnt().x) *
		Mat3::RotationY(obj.GetOrnt().y) *
		Mat3::RotationZ(obj.GetOrnt().z);
	
	pipeline.effect.vs.BindRotation(rot);
	pipeline.effect.vs.BindTranslation({ obj.GetPos().x, obj.GetPos().y, obj.GetPos().z });
   
	pipeline.Draw(obj.GetTriangle());
}