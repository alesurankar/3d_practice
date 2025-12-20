//#include "Scene2.h"
//
//Scene2::Scene2(Graphics& gfx)
//	:
//	gfx(gfx),
//	pipeline(gfx),
//	rng(rd()),
//	vRand(-10.0f, 10.0f),
//	pRand(-50.0f, 50.0f),
//	zRand(100.0f, 200.0f)
//{
//	int a = 0;
//	for (int i = 0; i < 200; i++) {
//		a += 40;
//		switch (a) {
//		case 40:
//			objects.emplace_back(std::make_unique<Thing>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\wood.bmp", 1.0f));
//			break;
//		case 80:
//			objects.emplace_back(std::make_unique<Thing>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\blue.bmp", 1.0f));
//			break; 
//		case 120:
//			objects.emplace_back(std::make_unique<Thing>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\ceiling.jpg", 1.0f));
//			break; 
//		case 160:
//			objects.emplace_back(std::make_unique<Thing>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\stonewall.jpg", 1.0f));
//			break;
//		case 199:
//			objects.emplace_back(std::make_unique<Thing>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\green.bmp", 1.0f));
//			break;
//		case 200:
//			objects.emplace_back(std::make_unique<Thing>(gfx, Vec3(pRand(rng), pRand(rng), zRand(rng)), L"Images\\red.bmp", 1.0f));
//			a = 0;
//			break;
//		}
//	}
//	for (auto& obj : objects) {
//		obj->SetVelocity(vRand(rng), vRand(rng), vRand(rng));
//		obj->SetTorque(vRand(rng), vRand(rng), vRand(rng));
//	}
//}
//
//
//void Scene2::Update(const Keyboard& kbd, Mouse& mouse, float dt)
//{
//	/*while (!mouse.IsEmpty())
//	{
//		Mouse::Event e = mouse.Read();
//
//		switch (e.GetType())
//		{
//		case Mouse::Event::Type::LPress:
//			Vec3 spawn = Vec3(0.0f, -1.0f, 2.0f);
//			Vec3 dest = Vec3(GetClickChords(mouse));
//			bullets.emplace_back(std::make_unique<Bullet>(gfx, spawn, dest, L"Images\\white.bmp", 0.2f));
//			break;
//		}
//	}*/
//	if (mouse.LeftIsPressed()) {
//		Vec3 spawn = Vec3(0.0f, -1.0f, 2.0f);
//		Vec3 dest = Vec3(GetClickChords(mouse));
//		bullets.emplace_back(std::make_unique<Bullet>(gfx, spawn, dest, L"Images\\white.bmp", 0.2f));
//	}
//
//	for (auto& obj : objects)  {
//		obj->Move(dt);
//		obj->Rotate(dt);
//	}
//	for (auto& bul : bullets)  {
//		bul->Move(dt);
//	}
//
//	CheckCollisions();
//	for (auto& obj : objects) {
//		if (obj->CheckCollisionFlag()) {
//			if (obj->CheckMoved() == false) {
//				obj->ChangeVelocity();
//				obj->ChangeTorque();
//				obj->SetMoved();
//			}
//		}
//	}
//	CheckDestroyed();
//}
//
//void Scene2::Draw()
//{
//	pipeline.BeginFrame();
//	for (auto& obj : objects) {
//		BindAndDraw(*obj);
//	}
//	for (auto& bul : bullets) {
//		BindAndDraw(*bul);
//	}
//}
//
//void Scene2::CheckCollisions()
//{
//	for (auto& obj : objects) {
//		obj->ResetCollisionFlag();
//	}
//	for (size_t i = 0; i < objects.size(); i++)
//	{
//		bool isColliding = false;
//		for (size_t j = 0; j < objects.size(); j++)
//		{
//			if (i == j) continue;
//
//			if (objects[i]->GetWorldBoundingBox()
//				.IsOverlappingWith(objects[j]->GetWorldBoundingBox()))
//			{
//				objects[i]->SetCollisionFlag();
//				isColliding = true;
//			}
//		}
//
//		if (!isColliding) {
//			objects[i]->ResetMoved();
//		}
//		
//		for (auto& bul : bullets) {
//			if (objects[i]->GetWorldBoundingBox()
//				.IsOverlappingWith(bul->GetWorldBoundingBox()))
//			{
//				bul->destroyed = true; 
//				objects[i]->destroyed = true;
//			}
//		}
//	}
//}
//
//void Scene2::CheckDestroyed()
//{
//	bullets.erase(
//		std::remove_if(bullets.begin(), bullets.end(),
//			[](const std::unique_ptr<Bullet>& b) {
//				return b->destroyed;
//			}),
//		bullets.end());
//	objects.erase(
//		std::remove_if(objects.begin(), objects.end(),
//			[](const std::unique_ptr<Thing>& o) {
//				return o->destroyed;
//			}),
//		objects.end());
//}
//
//void Scene2::BindAndDraw(const Thing& obj)
//{
//	pipeline.effect.ps.BindTexture(obj.GetTexture());
//	const auto proj = Mat4::ProjectionHFOV(fieldOfView, aspect, nearZ, farZ);
//	const Mat4 world =
//		Mat4::RotationX(obj.GetOrnt().x) *
//		Mat4::RotationY(obj.GetOrnt().y) *
//		Mat4::RotationZ(obj.GetOrnt().z) *
//		Mat4::Translation(obj.GetPos().x, obj.GetPos().y, obj.GetPos().z);
//
//	pipeline.effect.vs.BindWorld(world);
//	pipeline.effect.vs.BindProjection(proj);
//
//	pipeline.Draw(obj.GetTriangle());
//}
//
//Vec3 Scene2::GetClickChords(const Mouse& mouse)
//{
//	Vec2 mp = Vec2(mouse.GetPos());
//
//	float x = mp.x - Graphics::ScreenWidth * 0.5f;
//	float y = -(mp.y - Graphics::ScreenHeight * 0.5f);
//
//	return Vec3(x, y + 10.0f, 1000.0f);
//}