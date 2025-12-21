#include "Scene3.h"

Scene3::Scene3(Graphics& gfx)
	:
	sharedZ(std::make_shared<ZBuffer>(gfx.ScreenWidth, gfx.ScreenHeight)),
	litPipeline(gfx, sharedZ),
	unlitPipeline(gfx, sharedZ),
	rng(rd()),
	vRand(-0.2f, 0.2f),
	pRand(-50.0f, 50.0f),
	zRand(100.0f, 200.0f)
{
	//objects.emplace_back(std::make_unique<Thing>(gfx, Vec3(0.0f, 0.0f, 0.0f), L"Images\\stonewall.jpg", 4.0f));   //TextureEffect
	//objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 0.0f, 0.0f), 4.0f));							//SolidGeometryEffect
	//objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 0.0f, 0.0f), Sphere::GetPlain<SceneVertex>()));
	//objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 0.0f, 0.0f), Sphere::GetPlainNormals<SceneVertex>()));
	//objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 0.0f, 0.0f), Drawable::GetPlain<SceneVertex>()));
	lights.emplace_back(std::make_unique<Thing>(gfx, Vec3(0.0f, 0.0f, 0.0f), Sphere::GetPlainColor<SolidVertex>(0.1f)));
	lights[0]->Move(0.0f, 0.0f, 0.0f);
	lights[0]->Rotate(0.0f, 0.0f, 0.0f);
	player = lights.back().get();
	objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 0.0f, 10.0f), IndexedTriangleList<SceneVertex>::LoadNormals("models\\suzanne.obj")));
	objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 1.0f, 10.0f), Plane::GetNormals<SceneVertex>(10,4)));
	for (auto& obj : objects) {
		obj->SetVelocity(3 * vRand(rng), 3 * vRand(rng), 3 * vRand(rng));
		obj->SetTorque(vRand(rng), vRand(rng), vRand(rng));
	}
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
	for (auto& obj : objects) {
		obj->Move(dt);
		obj->Rotate(dt);
	}
	if (kbd.KeyIsPressed(VK_SPACE)) {
		speed = 2 * dt;
	}
	if (kbd.KeyIsPressed(VK_UP)) {
		cam_pos.y += speed;
	}
	if (kbd.KeyIsPressed(VK_DOWN)) {
		cam_pos.y -= speed;
	}
	if (kbd.KeyIsPressed(VK_LEFT)) {
		cam_pos.x -= speed;
	}
	if (kbd.KeyIsPressed(VK_RIGHT)) {
		cam_pos.x += speed;
	}
	if (kbd.KeyIsPressed('K')) {
		cam_pos.z -= speed;
	}
	if (kbd.KeyIsPressed('L')) {
		cam_pos.z += speed;
	}
}

void Scene3::Draw()
{
	litPipeline.BeginFrame();
	unlitPipeline.BeginFrame();
	light_pos = (player->GetPos());
	view = Mat4::Translation(-cam_pos);
	for (auto& obj : objects) {
		BindAndDrawObjects(*obj);
	}
	for (auto& lit : lights) {
		BindAndDrawLights(*lit);
	}
}

void Scene3::BindAndDrawObjects(const Thing2& obj)
{
	//pipeline.effect.ps.BindTexture(obj.GetTexture());                                          //TextureEffect
	
	//pipeline.effect.gs.BindColors(															 //SolidGeometryEffect
	//	{ Colors::Red,Colors::Green,Colors::Blue,Colors::Magenta,Colors::Yellow,Colors::Cyan }   //SolidGeometryEffect
	//);																						 //SolidGeometryEffect

	const Mat4 world =
		Mat4::RotationX(obj.GetOrnt().x) *
		Mat4::RotationY(obj.GetOrnt().y) *
		Mat4::RotationZ(obj.GetOrnt().z) *
		Mat4::Translation(obj.GetPos());

	litPipeline.effect.vs.BindWorld(world);
	litPipeline.effect.vs.BindView(view);
	litPipeline.effect.vs.BindProjection(proj);

	//litPipeline.effect.vs.SetLightPosition(player->GetPos());   //GouraudEffect
	litPipeline.effect.ps.SetLightPosition(light_pos);   //PhongEffect

	litPipeline.Draw(obj.GetTriangle());
}

void Scene3::BindAndDrawLights(const Thing& obj)
{
	unlitPipeline.effect.vs.BindWorldView(Mat4::Translation(light_pos) * view);
	unlitPipeline.effect.vs.BindProjection(proj);

	unlitPipeline.Draw(obj.GetTriangle());
}