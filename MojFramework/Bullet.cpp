#include "Bullet.h"

Bullet::Bullet(Graphics& gfx, const Vec3& pos_in, const std::wstring& filename, float size)
	:
	Thing(gfx, pos_in, filename, size)
{}

void Bullet::Move(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;

	CheckBorder();
}

void Bullet::CheckBorder()
{
	if (pos.x < -20.0f) {
		pos.x = -20.0f;
		vel.x = -vel.x;
		torq.x = -torq.x;
		destroyed = true;
	}
	if (pos.y < -20.0f) {
		pos.y = -20.0f;
		vel.y = -vel.y;
		torq.y = -torq.y;
		destroyed = true;
	}
	if (pos.z < 2.0f) {
		pos.z = 2.0f;
		vel.z = -vel.z;
		torq.z = -torq.z;
		destroyed = true;
	}
	if (pos.x > 20.0f) {
		pos.x = 20.0f;
		vel.x = -vel.x;
		torq.x = -torq.x;
		destroyed = true;
	}
	if (pos.y > 20.0f) {
		pos.y = 20.0f;
		vel.y = -vel.y;
		torq.y = -torq.y;
		destroyed = true;
	}
	if (pos.z > 120.0f) {
		pos.z = 120.0f;
		vel.z = -vel.z;
		torq.z = -torq.z;
		destroyed = true;
	}
	triangles = itlist;
}
