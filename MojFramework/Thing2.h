#pragma once
#include "Thing.h"
#include "SpecularPhongPointEffect.h"

class Thing2 : public Thing<SpecularPhongPointEffect>
{
public:
	using Effect = SpecularPhongPointEffect;
	Thing2(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<Effect::Vertex>&& tl, float size = 1.0f)
		:
		Thing<Effect>(gfx, pos_in, std::move(tl), size)
	{}
	void Draw(Pipeline<Effect>& pipeline) const
	{
		pipeline.effect.vs.BindWorld(GetWorld());
		pipeline.Draw(GetTriangle());
	}
private:
	Mat4 GetWorld() const noexcept
	{
		return Mat4(
			Mat4::RotationX(GetOrnt().x) *
			Mat4::RotationY(GetOrnt().y) *
			Mat4::RotationZ(GetOrnt().z) *
			Mat4::Translation(GetPosV3())
		);
	}
};