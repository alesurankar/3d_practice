#pragma once
#include "Thing.h"
#include "VertexLightTexturedEffect.h"

class Thing3 : public Thing<VertexLightTexturedEffect>
{
public:
	using Effect = VertexLightTexturedEffect;
	Thing3(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<Effect::Vertex> tl, const std::wstring& filename, float size = 1.0f);
	const Surface& GetTexture() const;
private:
	std::shared_ptr<Surface> pTexture;
};