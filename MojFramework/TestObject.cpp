#include "TestObject.h"
#include "App.h"
#include <utility>

TestObject::TestObject(Graphics& gfx, const Vec3& pos_in, const std::wstring& filename_in)
	:
	pos(pos_in),
	ornt({ 0.0f,0.0f,0.0f }),
	vel({ 0.0f,0.0f,0.0f }),
	torq({ 0.0f,0.0f,0.0f }),
	itlist(Drawable::GetSkinned<Vertex>()),
	triangles(itlist)
{
	pTexture = std::make_shared<Surface>(Surface::FromFile(filename_in));
}

void TestObject::Move(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;

	CheckBorder();
}

void TestObject::Move()
{
	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;

	CheckBorder();
}

void TestObject::Rotate(float x, float y, float z)
{
	ornt.x = wrap_angle(ornt.x + x);
	ornt.y = wrap_angle(ornt.y + y);
	ornt.z = wrap_angle(ornt.z + z);

	CheckBorder();
}

void TestObject::Rotate()
{
	ornt.x = wrap_angle(ornt.x + torq.x);
	ornt.y = wrap_angle(ornt.y + torq.y);
	ornt.z = wrap_angle(ornt.z + torq.z);

	CheckBorder();
}

void TestObject::CheckBorder()
{
	if (pos.x < -10.0f) {
		pos.x = -10.0f;
		vel.x = -vel.x;
		torq.x = -torq.x;
	}
	if (pos.y < -10.0f) {
		pos.y = -10.0f;
		vel.y = -vel.y;
		torq.y = -torq.y;
	}
	if (pos.z < 6.0f) {
		pos.z = 6.0f;
		vel.z = -vel.z;
		torq.z = -torq.z;
	}
	if (pos.x > 10.0f) {
		pos.x = 10.0f;
		vel.x = -vel.x;
		torq.x = -torq.x;
	}
	if (pos.y > 10.0f) {
		pos.y = 10.0f;
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

void TestObject::SetVelocity(float vx, float vy, float vz)
{
	vel = Vec3(vx, vy, vz);
}

void TestObject::ChangeVelocity()
{
	vel = -vel;
}

void TestObject::SetTorque(float tx, float ty, float tz)
{
	torq = Vec3(tx, ty, tz);
}

void TestObject::ChangeTorque()
{
	torq = -torq;
}

BoxF TestObject::GetWorldBoundingBox() const
{
	BoxF local = Drawable::GetLocalBoundingBox();

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

const Surface& TestObject::GetTexture() const
{
	return *pTexture;
}

void TestObject::SetCollisionFlag()
{
	collisionFlag = true;
}

void TestObject::ResetCollisionFlag()
{
	collisionFlag = false;
}

bool TestObject::CheckCollisionFlag()
{
	return collisionFlag;
}

void TestObject::SetMoved()
{
	moved = true;
}

void TestObject::ResetMoved()
{
	moved = false;
}

bool TestObject::CheckMoved()
{
	return moved;
}

Vec3 TestObject::GetPos() const
{
	return pos;
}

Vec3 TestObject::GetOrnt() const
{
	return ornt;
}

const IndexedTriangleList<TextureEffect::Vertex>& TestObject::GetTriangle() const
{
	return triangles;
}
