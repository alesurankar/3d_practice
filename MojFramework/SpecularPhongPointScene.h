#pragma once
#include "Scene.h"
#include "Mat.h"
#include "Pipeline.h"
#include "SpecularPhongPointEffect.h"
#include "SolidEffect.h"
#include "Sphere.h"
#include "MouseTracker.h"


class SpecularPhongPointScene : public Scene
{
public:
	typedef ::Pipeline<SpecularPhongPointEffect> Pipeline;
	typedef ::Pipeline<SolidEffect> LightIndicatorPipeline;
	typedef Pipeline::Vertex Vertex;
public:
	SpecularPhongPointScene(Graphics& gfx, IndexedTriangleList<Vertex> tl)
		:
		itlist(std::move(tl)),
		pZb(std::make_shared<ZBuffer>(gfx.ScreenWidth, gfx.ScreenHeight)),
		pipeline(gfx, pZb),
		liPipeline(gfx, pZb),
		Scene("phong point shader scene free mesh")
	{
		itlist.AdjustToTrueCenter();
		mod_pos.z = itlist.GetRadius() * 1.0f;
		for (auto& v : lightIndicator.vertices)
		{
			v.color = Colors::White;
		}
	}
	virtual void Draw() override
	{
		pipeline.BeginFrame();

		const auto proj = Mat4::ProjectionHFOV(hfov, aspect_ratio, 0.5f, 4.0f);
		const auto view = Mat4::Translation(-cam_pos) * cam_rot_inv;
		// set pipeline transform
		pipeline.effect.vs.BindWorld(
			Mat4::RotationX(theta_x) *
			Mat4::RotationY(theta_y) *
			Mat4::RotationZ(theta_z) *
			Mat4::Translation(mod_pos)
		);
		pipeline.effect.vs.BindView(view);
		pipeline.effect.vs.BindProjection(proj);
		pipeline.effect.ps.SetLightPosition(l_pos * view);
		// render triangles
		pipeline.Draw(itlist);

		// draw light indicator with different pipeline
		// don't call beginframe on this pipeline b/c wanna keep zbuffer contents
		// (don't like this assymetry but we'll live with it for now)
		liPipeline.effect.vs.BindWorldView(Mat4::Translation(l_pos) * view);
		liPipeline.effect.vs.BindProjection(proj);
		liPipeline.Draw(lightIndicator);
	}
private:
	IndexedTriangleList<Vertex> itlist;
	IndexedTriangleList<SolidEffect::Vertex> lightIndicator = Sphere::GetPlain<SolidEffect::Vertex>(0.05f);
	std::shared_ptr<ZBuffer> pZb;
	Pipeline pipeline;
	LightIndicatorPipeline liPipeline;
};