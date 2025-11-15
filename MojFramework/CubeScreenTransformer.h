#pragma once
#include "Vec3.h"
#include "Vec2.h"
#include "Graphics.h"

class CubeScreenTransformer
{
public:
	CubeScreenTransformer()
		:
		xFactor(float(Graphics::ScreenWidth) / 2.0f),
		yFactor(float(Graphics::ScreenHeight) / 2.0f)
	{
	}
	Vec3& Transform(Vec3& v) const
	{
		v.x = (v.x + 1.0f) * xFactor;
		v.y = (-v.y + 1.0f) * yFactor;
		return v;
	}

	Vec2& Transform2(Vec2& v) const
	{
		v.x = (v.x + 1.0f) * xFactor;
		v.y = (-v.y + 1.0f) * yFactor;
		return v;
	}
private:
	float xFactor;
	float yFactor;
};