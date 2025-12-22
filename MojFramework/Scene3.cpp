#include "Scene3.h"

Scene3::Scene3(Graphics& gfx)
	:
	pZb(std::make_shared<ZBuffer>(gfx.ScreenWidth, gfx.ScreenHeight)),
	litPipeline(gfx, pZb),
	unlitPipeline(gfx, pZb),
	texPipeline(gfx, pZb),
	rng(rd()),
	vRand(-0.2f, 0.2f),
	pRand(-50.0f, 50.0f),
	zRand(100.0f, 200.0f)
{
	lights.emplace_back(std::make_unique<Thing>(gfx, Vec3(0.0f, 0.0f, 0.0f), Sphere::GetPlainColor<SolidVertex>(0.1f)));
	lights[0]->Move(0.0f, 0.0f, 0.0f);
	lights[0]->Rotate(0.0f, 0.0f, 0.0f);
	light = lights.back().get();
	objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 0.0f, 10.0f), IndexedTriangleList<SpecularPhongPointVertex>::LoadNormals("models\\suzanne.obj")));
	objects.emplace_back(std::make_unique<Thing2>(gfx, Vec3(0.0f, 1.0f, 10.0f), Plane::GetNormals<SpecularPhongPointVertex>(4, 2)));
	for (auto& obj : objects) {
		obj->SetVelocity(3 * vRand(rng), 3 * vRand(rng), 3 * vRand(rng));
		obj->SetAngle(vRand(rng), vRand(rng), vRand(rng));
	}
	textures.emplace_back(std::make_unique<Thing3>(gfx, Vec3(0.0f, 0.0f, 5.0f), Plane::GetSkinnedNormals<VertexLightTexturedVertex>(10, 2.0f), L"Images\\stonewall.jpg"));
	for (auto& tex : textures) {
		tex->SetVelocity(vRand(rng), vRand(rng), vRand(rng));
		tex->SetAngle(vRand(rng), vRand(rng), vRand(rng));
	}
}


void Scene3::Update(const Keyboard& kbd, Mouse& mouse, float dt)
{
	//Light Position
	float speed = dt / 2;
	if (kbd.KeyIsPressed(VK_SPACE)) {
		speed = 2 * dt;
	}
	if (kbd.KeyIsPressed(VK_UP)) {
		light->Move(0.0f, speed, 0.0f);
	}
	if (kbd.KeyIsPressed(VK_DOWN)) {
		light->Move(0.0f, -speed, 0.0f);
	}
	if (kbd.KeyIsPressed(VK_LEFT)) {
		light->Move(-speed, 0.0f, 0.0f);
	}
	if (kbd.KeyIsPressed(VK_RIGHT)) {
		light->Move(speed, 0.0f, 0.0f);
	}
	if (kbd.KeyIsPressed('N')) {
		light->Move(0.0f, 0.0f, -speed);
	}
	if (kbd.KeyIsPressed('M')) {
		light->Move(0.0f, 0.0f, speed);
	}
	
	//Camera position
	if (kbd.KeyIsPressed('W')) {
		cam_pos += Vec4{ 0.0f,1.0f,0.0f,0.0f } *!cam_rot * speed;
	}
	if (kbd.KeyIsPressed('S')) {
		cam_pos += Vec4{ 0.0f,-1.0f,0.0f,0.0f } *!cam_rot * speed;
	}
	if (kbd.KeyIsPressed('A')) {
		cam_pos += Vec4{ -1.0f,0.0f,0.0f,0.0f } *!cam_rot * speed;
	}
	if (kbd.KeyIsPressed('D')) {
		cam_pos += Vec4{ 1.0f,0.0f,0.0f,0.0f } *!cam_rot * speed;
	}
	if (kbd.KeyIsPressed(VK_SHIFT)) {
		cam_pos += Vec4{ 0.0f,0.0f,1.0f,0.0f } *!cam_rot * speed;
	}
	if (kbd.KeyIsPressed(VK_CONTROL)) {
		cam_pos += Vec4{ 0.0f,0.0f,-1.0f,0.0f } *!cam_rot * speed;
	}
	if (kbd.KeyIsPressed('Q'))
	{
		cam_rot = cam_rot * Mat4::RotationZ(speed);
	}
	if (kbd.KeyIsPressed('E'))
	{
		cam_rot = cam_rot * Mat4::RotationZ(-speed);
	}

	//Camera Orientation
	while (!mouse.IsEmpty())
	{
		const auto e = mouse.Read();
		switch (e.GetType())
		{
		case Mouse::Event::Type::LPress:
			mt.Engage(e.GetPos());
			break;
		case Mouse::Event::Type::LRelease:
			mt.Release();
			break;
		case Mouse::Event::Type::Move:
			if (mt.Engaged())
			{
				const auto delta = mt.Move(e.GetPos());
				cam_rot = cam_rot
					* Mat4::RotationY((float)-delta.x * htrack)
					* Mat4::RotationX((float)-delta.y * vtrack);
			}
			break;
		}
	}

	//Updating Objects
	for (auto& obj : objects) {
		obj->Move(dt);
		obj->Rotate(dt);
	}
	for (auto& tex : textures) {
		tex->Move(dt);
		tex->Rotate(dt);
	}
}

void Scene3::Draw()
{
	litPipeline.BeginFrame();
	light_pos = (light->GetPos());
	view = Mat4::Translation(-cam_pos) * cam_rot;
	for (auto& lit : lights) {
		BindAndDrawLights(*lit);
	}
	for (auto& obj : objects) {
		BindAndDrawObjects(*obj);
	}
	for (auto& tex : textures) {
		BindAndDrawTexture(*tex);
	}
}

void Scene3::BindAndDrawLights(const Thing& obj)
{
	const Mat4 world = Mat4::Translation(light_pos);

	unlitPipeline.effect.vs.BindWorld(world);
	unlitPipeline.effect.vs.BindView(view);
	unlitPipeline.effect.vs.BindProjection(proj);

	unlitPipeline.Draw(obj.GetTriangle());
}

void Scene3::BindAndDrawObjects(const Thing2& obj)
{
	const Mat4 world =
		Mat4::RotationX(obj.GetOrnt().x) *
		Mat4::RotationY(obj.GetOrnt().y) *
		Mat4::RotationZ(obj.GetOrnt().z) *
		Mat4::Translation(obj.GetPos());

	litPipeline.effect.vs.BindWorld(world);
	litPipeline.effect.vs.BindView(view);
	litPipeline.effect.vs.BindProjection(proj);
	litPipeline.effect.ps.SetLightPosition(light_pos);

	litPipeline.Draw(obj.GetTriangle());
}

void Scene3::BindAndDrawTexture(const Thing3& obj)
{
	texPipeline.effect.ps.BindTexture(obj.GetTexture()); 

	const Mat4 world =
		Mat4::RotationX(obj.GetOrnt().x) *
		Mat4::RotationY(obj.GetOrnt().y) *
		Mat4::RotationZ(obj.GetOrnt().z) *
		Mat4::Translation(obj.GetPos());

	texPipeline.effect.vs.BindWorld(world);
	texPipeline.effect.vs.BindView(view); 
	texPipeline.effect.vs.BindProjection(proj);
	texPipeline.effect.vs.SetLightPosition(light_pos);

	texPipeline.Draw(obj.GetTriangle());
}