#include "Thing.h"
#include "App.h"
#include <utility>

Thing::Thing(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<SolidVertex> tl, float size_in)
	:
	pos(pos_in),
	ornt({ 0.0f,0.0f,0.0f }),
	vel({ 0.0f,0.0f,0.0f }),
	torq({ 0.0f,0.0f,0.0f }),
	size(size_in),
	itlist(std::move(tl))
{
	//pTexture = std::make_shared<Surface>(Surface::FromFile(filename_in));   //TextureEffect
	itlist.AdjustToTrueCenter();
	pos.x = itlist.GetRadius();
	triangles = itlist;
}

void Thing::Move(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;

	CheckBorder();
}

void Thing::Move(float dt)
{
	pos.x += vel.x * dt;
	pos.y += vel.y * dt;
	pos.z += vel.z * dt;

	CheckBorder();
}

void Thing::Rotate(float x, float y, float z)
{
	ornt.x = wrap_angle(ornt.x + x);
	ornt.y = wrap_angle(ornt.y + y);
	ornt.z = wrap_angle(ornt.z + z);

	CheckBorder();
}

void Thing::Rotate(float dt)
{
	ornt.x = wrap_angle(ornt.x + torq.x * dt);
	ornt.y = wrap_angle(ornt.y + torq.y * dt);
	ornt.z = wrap_angle(ornt.z + torq.z * dt);

	CheckBorder();
}

void Thing::CheckBorder()
{
	if (pos.x < -6.0) {
		pos.x = -6.0f;
		vel.x = -vel.x;
		torq.x = -torq.x;
	}
	if (pos.y < -6.0f) {
		pos.y = -6.0f;
		vel.y = -vel.y;
		torq.y = -torq.y;
	}
	if (pos.z < 3.0f) {
		pos.z = 3.0f;
		vel.z = -vel.z;
		torq.z = -torq.z;
	}
	if (pos.x > 6.0f) {
		pos.x = 6.0f;
		vel.x = -vel.x;
		torq.x = -torq.x;
	}
	if (pos.y > 6.0f) {
		pos.y = 6.0f;
		vel.y = -vel.y;
		torq.y = -torq.y;
	}
	if (pos.z > 20.0f) {
		pos.z = 20.0f;
		vel.z = -vel.z;
		torq.z = -torq.z;
	}
	triangles = itlist;
}

void Thing::SetVelocity(float vx, float vy, float vz)
{
	vel = Vec3(vx, vy, vz);
}

void Thing::ChangeVelocity()
{
	vel = -vel;
}

void Thing::SetTorque(float tx, float ty, float tz)
{
	torq = Vec3(tx, ty, tz);
}

void Thing::ChangeTorque()
{
	torq = -torq;
}

BoxF Thing::GetWorldBoundingBox() const
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

void Thing::SetCollisionFlag()
{
	collisionFlag = true;
}

void Thing::ResetCollisionFlag()
{
	collisionFlag = false;
}

bool Thing::CheckCollisionFlag()
{
	return collisionFlag;
}

void Thing::SetMoved()
{
	moved = true;
}

void Thing::ResetMoved()
{
	moved = false;
}

bool Thing::CheckMoved()
{
	return moved;
}

Vec3 Thing::GetPos() const
{
	return pos;
}

Vec3 Thing::GetOrnt() const
{
	return ornt;
}

const IndexedTriangleList<SolidVertex>& Thing::GetTriangle() const
{
	return triangles;
}
