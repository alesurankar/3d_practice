#include "Thing3.h"
#include "App.h"
#include <utility>

Thing3::Thing3(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<Effect::Vertex> tl, const std::wstring& filename, float size_in)
	:
	Thing(gfx, pos_in, std::move(tl), size_in)
{
	pTexture = std::make_shared<Surface>(Surface::FromFile(filename));
}

const Surface& Thing3::GetTexture() const
{
	return *pTexture;
}