#pragma once
#include "Thing.h"

class Bullet : public Thing
{
public:
	Bullet(Graphics& gfx, const Vec3& pos_in, const std::wstring& filename, float size = 1.0f); 
	void Move(float x, float y, float z);
	void CheckBorder();
};