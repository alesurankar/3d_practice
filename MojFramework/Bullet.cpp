//#include "Bullet.h"
//
//Bullet::Bullet(Graphics& gfx, const Vec3& pos_in, const Vec3& dest, const std::wstring& filename, float size)
//	:
//	Thing(gfx, pos_in, filename, size)
//{
//	Vec3 dir = dest - pos_in;
//
//	if (dir.LenSq() > 0.0001f)
//	{
//		dir.Normalize();
//	}
//
//	vel = dir * 300.0f;
//}
//
//void Bullet::Move(float dt)
//{
//	pos.x += vel.x * dt;
//	pos.y += vel.y * dt;
//	pos.z += vel.z * dt;
//
//	CheckBorder();
//}
//
//void Bullet::CheckBorder()
//{
//	if (pos.x < -60.0f) {
//		pos.x = -60.0f;
//		vel.x = -vel.x;
//		torq.x = -torq.x;
//		destroyed = true;
//	}
//	if (pos.y < -60.0f) {
//		pos.y = -60.0f;
//		vel.y = -vel.y;
//		torq.y = -torq.y;
//		destroyed = true;
//	}
//	if (pos.z < 0.0f) {
//		pos.z = 0.0f;
//		vel.z = -vel.z;
//		torq.z = -torq.z;
//		destroyed = true;
//	}
//	if (pos.x > 60.0f) {
//		pos.x = 60.0f;
//		vel.x = -vel.x;
//		torq.x = -torq.x;
//		destroyed = true;
//	}
//	if (pos.y > 60.0f) {
//		pos.y = 60.0f;
//		vel.y = -vel.y;
//		torq.y = -torq.y;
//		destroyed = true;
//	}
//	if (pos.z > 220.0f) {
//		pos.z = 220.0f;
//		vel.z = -vel.z;
//		torq.z = -torq.z;
//		destroyed = true;
//	}
//	triangles = itlist;
//}
