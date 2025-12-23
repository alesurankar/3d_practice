#include "Scene.h"

Scene::Scene(Graphics& gfx)
	:
	pZb(gfx.ScreenWidth, gfx.ScreenHeight),
	unlitPipeline(gfx, pZb),
	litPipeline(gfx, pZb),
	texPipeline(gfx, pZb),
	proj(Mat4::ProjectionHFOV(hfov, aspect_ratio, nearZ, farZ))
{
	// Lights
	lights.emplace_back(std::make_unique<Thing1>(gfx, rn.RndVec3(0.0f, 2.0f), Sphere::GetPlainColor<Thing1::Effect::Vertex>(0.1f)));
	light = lights.back().get();

	//Objects
	objects.emplace_back(std::make_unique<Thing2>(gfx, rn.RndVec3(1.0f, 4.0f), IndexedTriangleList<Thing2::Effect::Vertex>::LoadNormals("models\\suzanne.obj")));
	objects.emplace_back(std::make_unique<Thing2>(gfx, rn.RndVec3(1.0f, 4.0f), Plane::GetNormals<Thing2::Effect::Vertex>()));
	
	//Textures
	textures.emplace_back(std::make_unique<Thing3>(gfx, rn.RndVec3(1.0f, 4.0f), Plane::GetSkinnedNormals<Thing3::Effect::Vertex>(), L"Images\\stonewall.jpg"));
	for (const auto& obj : objects) {
		obj->SetVelocity(rn.RndVec3(-0.0f, 0.0f));
		obj->SetAngle(rn.RndVec3(-0.0f, 0.0f));
	}
	for (const auto& tex : textures) {
		tex->SetVelocity(rn.RndVec3(-0.0f, 0.0f));
		tex->SetAngle(rn.RndVec3(-0.0f, 0.0f));
	}
}


void Scene::Update(const Keyboard& kbd, Mouse& mouse, float dt)
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
		cam_pos += Vec4{ 0.0f,speed,0.0f,0.0f } *!cam_rot;
	}
	if (kbd.KeyIsPressed('S')) {
		cam_pos += Vec4{ 0.0f,-speed,0.0f,0.0f } *!cam_rot;
	}
	if (kbd.KeyIsPressed('A')) {
		cam_pos += Vec4{ -speed,0.0f,0.0f,0.0f } *!cam_rot;
	}
	if (kbd.KeyIsPressed('D')) {
		cam_pos += Vec4{ speed,0.0f,0.0f,0.0f } *!cam_rot;
	}
	if (kbd.KeyIsPressed(VK_SHIFT)) {
		cam_pos += Vec4{ 0.0f,0.0f,speed,0.0f } *!cam_rot;
	}
	if (kbd.KeyIsPressed(VK_CONTROL)) {
		cam_pos += Vec4{ 0.0f,0.0f,-speed,0.0f } *!cam_rot;
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
	for (const auto& obj : objects) {
		obj->Move(dt);
		obj->Rotate(dt);
	}
	for (const auto& tex : textures) {
		tex->Move(dt);
		tex->Rotate(dt);
	}
}

void Scene::BindAndDraw()
{
	unlitPipeline.BeginFrame();
	litPipeline.BeginFrame();
	texPipeline.BeginFrame();
	BindToPipelines();
	for (const auto& lit : lights) {
		DrawLights(*lit);
	}
	for (const auto& obj : objects) {
		DrawObjects(*obj);
	}
	for (const auto& tex : textures) {
		DrawTexture(*tex);
	}
}

void Scene::BindToPipelines()
{
	const Mat4 view = Mat4::Translation(-cam_pos) * cam_rot;
	const Vec4 light_pos = light->GetPosV4();
	unlitPipeline.effect.vs.BindView(view);
	unlitPipeline.effect.vs.BindProjection(proj);

	litPipeline.effect.vs.BindView(view);
	litPipeline.effect.vs.BindProjection(proj);
	litPipeline.effect.ps.SetLightPosition(light_pos * view);

	texPipeline.effect.vs.BindView(view);
	texPipeline.effect.vs.BindProjection(proj);
	texPipeline.effect.vs.SetLightPosition(light_pos * view);
}

void Scene::DrawLights(const Thing1& obj)
{
	unlitPipeline.effect.vs.BindWorld(obj.GetWorld());
	unlitPipeline.Draw(obj.GetTriangle());
}

void Scene::DrawObjects(const Thing2& obj)
{
	litPipeline.effect.vs.BindWorld(obj.GetWorld());
	litPipeline.Draw(obj.GetTriangle());
}

void Scene::DrawTexture(const Thing3& obj)
{
	texPipeline.effect.ps.BindTexture(obj.GetTexture());
	texPipeline.effect.vs.BindWorld(obj.GetWorld());
	texPipeline.Draw(obj.GetTriangle());
}