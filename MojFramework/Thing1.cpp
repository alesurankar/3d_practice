#include "Thing1.h"
#include "App.h"
#include <utility>

Thing1::Thing1(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<Effect::Vertex> tl, float size_in)
	:
	Thing<Effect>(gfx, pos_in, std::move(tl), size_in)
{}