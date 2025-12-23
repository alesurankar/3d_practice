#pragma once
#include "Thing.h"
#include "VertexLightTexturedEffect.h"

class Thing3 : public Thing<VertexLightTexturedEffect>
{
public:
	using Effect = VertexLightTexturedEffect;
	Thing3(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<Effect::Vertex>&& tl, const std::wstring& filename, float size = 1.0f)
		:
		Thing(gfx, pos_in, std::move(tl), size)
	{
		pTexture = std::make_shared<Surface>(Surface::FromFile(filename));
	}
	const Surface& GetTexture() const noexcept
	{
		return *pTexture;
	}
	Mat4 GetWorld() const noexcept
	{
		return Mat4(
			Mat4::RotationX(GetOrnt().x) *
			Mat4::RotationY(GetOrnt().y) *
			Mat4::RotationZ(GetOrnt().z) *
			Mat4::Translation(GetPosV3())
		);
	}
private:
	std::shared_ptr<Surface> pTexture;
};