#include "Thing3.h"
#include "App.h"
#include <utility>

Thing3::Thing3(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<VertexLightTexturedVertex> tl, const std::wstring& filename, float size_in)
	:
	pos(pos_in),
	ornt({ 0.0f,0.0f,0.0f }),
	vel({ 0.0f,0.0f,0.0f }),
	ang({ 0.0f,0.0f,0.0f }),
	size(size_in),
	itlist(std::move(tl))
{
	pTexture = std::make_shared<Surface>(Surface::FromFile(filename));
	itlist.AdjustToTrueCenter();
	pos.z = itlist.GetRadius() * 1.6f;
	triangles = itlist;
}

void Thing3::Move(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;

	CheckBorder();
}

void Thing3::Move(float dt)
{
	pos.x += vel.x * dt;
	pos.y += vel.y * dt;
	pos.z += vel.z * dt;

	CheckBorder();
}

void Thing3::Rotate(float x, float y, float z)
{
	ornt.x = wrap_angle(ornt.x + x);
	ornt.y = wrap_angle(ornt.y + y);
	ornt.z = wrap_angle(ornt.z + z);

	CheckBorder();
}

void Thing3::Rotate(float dt)
{
	ornt.x = wrap_angle(ornt.x + ang.x * dt);
	ornt.y = wrap_angle(ornt.y + ang.y * dt);
	ornt.z = wrap_angle(ornt.z + ang.z * dt);

	CheckBorder();
}

void Thing3::CheckBorder()
{
	if (pos.x < -6.0) {
		pos.x = -6.0f;
		vel.x = -vel.x;
		ang.x = -ang.x;
	}
	if (pos.y < -6.0f) {
		pos.y = -6.0f;
		vel.y = -vel.y;
		ang.y = -ang.y;
	}
	if (pos.z < 3.0f) {
		pos.z = 3.0f;
		vel.z = -vel.z;
		ang.z = -ang.z;
	}
	if (pos.x > 6.0f) {
		pos.x = 6.0f;
		vel.x = -vel.x;
		ang.x = -ang.x;
	}
	if (pos.y > 6.0f) {
		pos.y = 6.0f;
		vel.y = -vel.y;
		ang.y = -ang.y;
	}
	if (pos.z > 20.0f) {
		pos.z = 20.0f;
		vel.z = -vel.z;
		ang.z = -ang.z;
	}
	triangles = itlist;
}

void Thing3::SetVelocity(float vx, float vy, float vz)
{
	vel = Vec3(vx, vy, vz);
}

void Thing3::ChangeVelocity()
{
	vel = -vel;
}

void Thing3::SetAngle(float ax, float ay, float az)
{
	ang = Vec3(ax, ay, az);
}

void Thing3::ChangeAngle()
{
	ang = -ang;
}

BoxF Thing3::GetWorldBoundingBox() const
{
	BoxF local = Squere::GetLocalBoundingBox(size);

	const Vec3& p = pos;
	return BoxF(
		local.left + p.x,
		local.top + p.y,
		local.front + p.z,
		local.right + p.x,
		local.bottom + p.y,
		local.back + p.z
	);
}

const Surface& Thing3::GetTexture() const
{
	return *pTexture;
}

void Thing3::SetCollisionFlag()
{
	collisionFlag = true;
}

void Thing3::ResetCollisionFlag()
{
	collisionFlag = false;
}

bool Thing3::CheckCollisionFlag()
{
	return collisionFlag;
}

void Thing3::SetMoved()
{
	moved = true;
}

void Thing3::ResetMoved()
{
	moved = false;
}

bool Thing3::CheckMoved()
{
	return moved;
}

Vec3 Thing3::GetPos() const
{
	return pos;
}

Vec3 Thing3::GetOrnt() const
{
	return ornt;
}

const IndexedTriangleList<VertexLightTexturedVertex>& Thing3::GetTriangle() const
{
	return triangles;
}
