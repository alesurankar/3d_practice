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
	lights.emplace_back(std::make_unique<Thing1>(gfx, rn.RndVec3(0.0f, 2.0f), Sphere::GetPlainColor<Thing1::Effect::Vertex>(0.2f)));
	light = lights.back().get();

	//Objects
	objects.emplace_back(std::make_unique<Thing2>(gfx, rn.RndVec3(1.0f, 4.0f), IndexedTriangleList<Thing2::Effect::Vertex>::LoadNormals("models\\suzanne.obj")));
	objects.emplace_back(std::make_unique<Thing2>(gfx, rn.RndVec3(1.0f, 4.0f), Plane::GetNormals<Thing2::Effect::Vertex>()));
	
	//Textures
	textures.emplace_back(std::make_unique<Thing3>(gfx, rn.RndVec3(1.0f, 4.0f), Plane::GetSkinnedNormals<Thing3::Effect::Vertex>(), L"Images\\stonewall.jpg"));
	for (const auto& obj : objects) {
		obj->SetVelocity(rn.RndVec3(-0.1f, 0.1f));
		obj->SetAngle(rn.RndVec3(-0.1f, 0.1f));
	}
	for (const auto& tex : textures) {
		tex->SetVelocity(rn.RndVec3(-0.1f, 0.1f));
		tex->SetAngle(rn.RndVec3(-0.1f, 0.1f));
	}
}


void Scene::Update(const Keyboard& kbd, Mouse& mouse, float dt)
{
	float speed = dt / 2;
	if (kbd.KeyIsPressed(VK_SPACE)) {
		speed = 2 * dt;
	}

	//Light Position
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
		cam_pos += Vec4{ 0.0f,speed,0.0f,0.0f } *cam_rot;
	}
	if (kbd.KeyIsPressed('S')) {
		cam_pos += Vec4{ 0.0f,-speed,0.0f,0.0f } *cam_rot;
	}
	if (kbd.KeyIsPressed('A')) {
		cam_pos += Vec4{ -speed,0.0f,0.0f,0.0f } *cam_rot;
	}
	if (kbd.KeyIsPressed('D')) {
		cam_pos += Vec4{ speed,0.0f,0.0f,0.0f } *cam_rot;
	}
	if (kbd.KeyIsPressed(VK_SHIFT)) {
		cam_pos += Vec4{ 0.0f,0.0f,speed,0.0f } *cam_rot;
	}
	if (kbd.KeyIsPressed(VK_CONTROL)) {
		cam_pos += Vec4{ 0.0f,0.0f,-speed,0.0f } *cam_rot;
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
					* Mat4::RotationY((float)delta.x * htrack)
					* Mat4::RotationX((float)delta.y * vtrack);
			}
			break;
		}
	}

	//Updating Objects
	for (const auto& obj : objects) {
		obj->Update(dt);
	}
	for (const auto& tex : textures) {
		tex->Update(dt);
	}
}

void Scene::BindAndDraw()
{
	const FrustumView frustum = FrustumView::BuildViewFrustum(hfov, aspect_ratio, nearZ, farZ);
	BindToPipelines();
	view = Mat4::Translation(-cam_pos) * !cam_rot;

	for (const auto& lit : lights) {
		Vec4 c4 = lit->GetPosV4() * view;
		Vec3 centerVS = { c4.x, c4.y, c4.z };

		if (!FrustumView::IsVisible_ViewSpace(centerVS, lit->GetRadius(), frustum))
   			continue;
		lit->Draw(unlitPipeline);
	}
	for (const auto& obj : objects) {
		Vec4 c4 = Vec4(obj->GetPosV3(), 1.0f) * view;
		Vec3 centerVS = { c4.x, c4.y, c4.z };

		if (!FrustumView::IsVisible_ViewSpace(centerVS, obj->GetRadius(), frustum))
			continue;
		obj->Draw(litPipeline);
	}
	for (const auto& tex : textures) {
		Vec4 c4 = Vec4(tex->GetPosV3(), 1.0f) * view;
		Vec3 centerVS = { c4.x, c4.y, c4.z };

		if (!FrustumView::IsVisible_ViewSpace(centerVS, tex->GetRadius(), frustum))
			continue;
		tex->Draw(texPipeline);
	}
}

void Scene::BindToPipelines()
{
	unlitPipeline.BeginFrame();
	litPipeline.BeginFrame();
	texPipeline.BeginFrame();

	Vec4 light_pos = light->GetPosV4();

	unlitPipeline.effect.vs.BindView(view);
	unlitPipeline.effect.vs.BindProjection(proj);

	litPipeline.effect.vs.BindView(view);
	litPipeline.effect.vs.BindProjection(proj);
	litPipeline.effect.ps.SetLightPosition(light_pos * view);

	texPipeline.effect.vs.BindView(view);
	texPipeline.effect.vs.BindProjection(proj);
	texPipeline.effect.vs.SetLightPosition(light_pos * view);
}