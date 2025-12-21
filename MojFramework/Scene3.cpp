#include "Scene3.h"

Scene3::Scene3(Graphics& gfx)
	:
	pipeline(gfx)
{
	//objects.emplace_back(std::make_unique<Thing>(gfx, Vec3(0.0f, 0.0f, 0.0f), L"Images\\stonewall.jpg", 4.0f));   //TextureEffect
	//objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 0.0f, 0.0f), 4.0f));							//SolidGeometryEffect
	objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 0.0f, 0.0f), Sphere::GetPlain<SceneVertex>()));
	//objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 0.0f, 0.0f), Drawable::GetPlain<SceneVertex>()));
	objects[0]->Move(0.0f, 0.0f, 0.0f);
	objects[0]->Rotate(0.0f, 0.0f, 0.0f);
	player = objects.back().get();
	//for (auto& obj : objects) {
	//	obj->SetVelocity(1.0f, -1.0f, 1.0f);
	//	obj->SetTorque(0.3f, 0.3f, 0.3f);
	//}
}


void Scene3::Update(const Keyboard& kbd, Mouse& mouse, float dt)
{
	float speed = dt / 2;
	if (kbd.KeyIsPressed(VK_SPACE)) {
		speed = 2 * dt;
	}
	if (kbd.KeyIsPressed('W')) {
		player->Move(0.0f, speed, 0.0f);
	}
	if (kbd.KeyIsPressed('S')) {
		player->Move(0.0f, -speed, 0.0f);
	}
	if (kbd.KeyIsPressed('A')) {
		player->Move(-speed, 0.0f, 0.0f);
	}
	if (kbd.KeyIsPressed('D')) {
		player->Move(speed, 0.0f, 0.0f);
	}
	if (kbd.KeyIsPressed(VK_SHIFT)) {
		player->Move(0.0f, 0.0f, speed);
	}
	if (kbd.KeyIsPressed(VK_CONTROL)) {
		player->Move(0.0f, 0.0f, -speed);
	}
	if (kbd.KeyIsPressed('Q')) {
		player->Rotate(0.0f, 0.0f, speed);
	}
	if (kbd.KeyIsPressed('E')) {
		player->Rotate(0.0f, 0.0f, -speed);
	}
	//for (auto& obj : objects) {
	//	obj->Move(dt);
	//	obj->Rotate(dt);
	//}
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
	//pipeline.effect.ps.BindTexture(obj.GetTexture());                                          //TextureEffect
	
	//pipeline.effect.gs.BindColors(															 //SolidGeometryEffect
	//	{ Colors::Red,Colors::Green,Colors::Blue,Colors::Magenta,Colors::Yellow,Colors::Cyan }   //SolidGeometryEffect
	//);																						 //SolidGeometryEffect

	
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

	const Vec3 trans = { obj.GetPos().x, obj.GetPos().y, obj.GetPos().z };

	pipeline.effect.vs.BindRotation(rot);
	pipeline.effect.vs.BindTranslation(trans);

	const Mat3 light_rot =                                                                     // GeometryFlatEffect
		Mat3::RotationX(obj.GetOrnt().x + 1.0f) *											   // GeometryFlatEffect
		Mat3::RotationY(obj.GetOrnt().y + 1.0f) *											   // GeometryFlatEffect
		Mat3::RotationZ(obj.GetOrnt().z + 1.0f);											   // GeometryFlatEffect
	//Vec3 light_dir = { 0.2f,-0.5f,1.0f };                                                    // VertexFlatEffect
	//pipeline.effect.vs.SetLightDirection(light_dir * light_rot);							   // VertexFlatEffect
   
	pipeline.Draw(obj.GetTriangle());
}