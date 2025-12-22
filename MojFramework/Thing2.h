#pragma once
#include "Thing.h"
#include "SpecularPhongPointEffect.h"

class Thing2 : public Thing<SpecularPhongPointEffect>
{
public:
	using Effect = SpecularPhongPointEffect;
	Thing2(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<Effect::Vertex> tl, float size = 1.0f)
		:
		Thing<Effect>(gfx, pos_in, std::move(tl), size)
	{}
};