#include "Scene.h"

Scene::Scene(Graphics& gfx)
	:
	pipeline(gfx),
	rng(rd()),
	vRand(-0.05f, 0.05f),
	pRand(-5.0f, 5.0f),
	zRand(10.0f, 18.0f)
{
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\stonewall.bmp"));
	objects[0]->Move(0.0f, 0.0f, 0.0f);
	objects[0]->Rotate(0.0f, 0.0f, 0.0f);
	player = objects.back().get();
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\floor.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\ceiling.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\wood.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\wall.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\office_skin.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\office_skin_lores.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\white.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\white.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\white.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\Blue.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\Blue.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\Blue.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\Blue.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\Red.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\Red.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\Red.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\Green.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\Green.bmp"));
	objects.emplace_back(std::make_unique<TestObject>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\Green.bmp"));
	for (auto& obj : objects) {
		if (obj.get() != player) {
			obj->SetVelocity(vRand(rng), vRand(rng), vRand(rng));
			obj->SetTorque(vRand(rng), vRand(rng), vRand(rng));
		}
	}
}


void Scene::Update(const Keyboard& kbd, Mouse& mouse, float dt)
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
	/*while (!mouse.IsEmpty())
	{
		Mouse::Event e = mouse.Read();

		switch (e.GetType())
		{
		case Mouse::Event::Type::WheelUp:
			player->Move(0.0f, 0.0f, speed);
			break;

		case Mouse::Event::Type::WheelDown:
			player->Move(0.0f, 0.0f, -speed);
			break;
		}
	}*/
	if (kbd.KeyIsPressed('Q')) {
		player->Rotate(0.0f, 0.0f, speed);
	}
	if (kbd.KeyIsPressed('E')) {
		player->Rotate(0.0f, 0.0f, -speed);
	}
	for (auto& obj : objects) {
		if (obj.get() != player) {
			obj->Move();
			obj->Rotate();
		}
	}
	CheckCollisions();
	for (auto& obj : objects) {
		if (obj->CheckCollisionFlag()) {
			if (obj->CheckMoved() == false) {
				obj->ChangeVelocity();
				obj->ChangeTorque();
				obj->SetMoved();
			}
		}
	}
}

void Scene::Draw()
{
	pipeline.BeginFrame();
	for (auto& obj : objects) {
		BindAndDraw(*obj);
	}
}

void Scene::CheckCollisions()
{
	for (auto& obj : objects) {
		obj->ResetCollisionFlag();
	}
	for (size_t i = 0; i < objects.size(); i++)
	{
		bool isColliding = false;
		for (size_t j = 0; j < objects.size(); j++)
		{
			if (i == j) continue;

			if (objects[i]->GetWorldBoundingBox()
				.IsOverlappingWith(objects[j]->GetWorldBoundingBox()))
			{
				objects[i]->SetCollisionFlag();
				isColliding = true;
			}
		}

		// Only reset moved if object is truly not colliding with anyone
		if (!isColliding) {
			objects[i]->ResetMoved();
		}
	}
}

void Scene::BindAndDraw(const TestObject& obj)
{
    pipeline.effect.ps.BindTexture(obj.GetTexture());
    pipeline.effect.vs.BindTransformation(
        Mat4::RotationX(obj.GetOrnt().x) *
        Mat4::RotationY(obj.GetOrnt().y) *
        Mat4::RotationZ(obj.GetOrnt().z) *
        Mat4::Translation(obj.GetPos().x, obj.GetPos().y, obj.GetPos().z)
    );

    pipeline.Draw(obj.GetTriangle());
} 