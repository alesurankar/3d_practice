#pragma once
#include "Thing.h"
#include "SolidEffect.h"

class Thing1 : public Thing<SolidEffect>
{
public:
	using Effect = SolidEffect;
	Thing1(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<Effect::Vertex>&& tl, float size = 1.0f)
		:
		Thing<Effect>(gfx, pos_in, std::move(tl), size)
	{}
	Mat4 GetWorld() const noexcept
    {
		return Mat4::Translation(GetPosV4());
    }
};