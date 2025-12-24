#pragma once
#include "Squere.h"
#include "Sphere.h"
#include "Graphics.h"
#include "Vec3.h"
#include "Mat.h"
#include "Pipeline.h"
#include <memory>
#include <utility>

template<class Effect>
class Thing
{
public:
	using Vertex = typename Effect::Vertex;
	Thing(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<Vertex>&& tl, float size_in)
		:
		pos(pos_in),
		ornt({ 0.0f,0.0f,0.0f }),
		vel({ 0.0f,0.0f,0.0f }),
		ang({ 0.0f,0.0f,0.0f }),
		size(size_in),
		triangles(std::move(tl))
	{
		triangles.AdjustToTrueCenter();
		boundingRadius = triangles.GetRadius() * size;
		CheckBorder();
	}
	void Update(float dt)
	{
		Move(dt);
		Rotate(dt);
	}
	void Move(float x, float y, float z)
	{
		pos.x += x;
		pos.y += y;
		pos.z += z;

		CheckBorder();
	}
	void Rotate(float x, float y, float z)
	{
		ornt.x = wrap_angle(ornt.x + x);
		ornt.y = wrap_angle(ornt.y + y);
		ornt.z = wrap_angle(ornt.z + z);
	}
	Vec3 GetPosV3() const noexcept
	{
		return pos;
	}
	Vec4 GetPosV4() const noexcept
	{
		return Vec4(Vec3(pos), 1.0f);
	}
	Vec3 GetOrnt() const noexcept
	{
		return ornt;
	}
	const IndexedTriangleList<Vertex>& GetTriangle() const noexcept
	{
		return triangles;
	}
	void SetVelocity(float vx, float vy, float vz) noexcept
	{
		vel = Vec3(vx, vy, vz);
	}
	void SetVelocity(const Vec3& v) noexcept
	{
		SetVelocity(v.x, v.y, v.z);
	}
	void ChangeVelocity() noexcept
	{
		vel = -vel;
	}
	void SetAngle(float ax, float ay, float az) noexcept
	{
		ang = Vec3(ax, ay, az);
	}
	void SetAngle(const Vec3& a) noexcept
	{
		SetAngle(a.x, a.y, a.z);
	}
	void ChangeAngle() noexcept
	{
		ang = -ang;
	}
	float GetRadius() const noexcept
	{
		return boundingRadius;
	}
	BoxF GetWorldBoundingBox() const noexcept
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
	void SetCollisionFlag() noexcept
	{
		collisionFlag = true;
	}
	void ResetCollisionFlag() noexcept
	{
		collisionFlag = false;
	}
	bool CheckCollisionFlag() const noexcept
	{
		return collisionFlag;
	}
	void SetMoved() noexcept
	{
		moved = true;
	}
	void ResetMoved() noexcept
	{
		moved = false;
	}
	bool CheckMoved() const noexcept
	{
		return moved;
	}
private:
	void Move(float dt)
	{
		pos.x += vel.x * dt;
		pos.y += vel.y * dt;
		pos.z += vel.z * dt;

		CheckBorder();
	}
	void Rotate(float dt)
	{
		ornt.x = wrap_angle(ornt.x + ang.x * dt);
		ornt.y = wrap_angle(ornt.y + ang.y * dt);
		ornt.z = wrap_angle(ornt.z + ang.z * dt);
	}
	void CheckBorder()
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
	}
private:
	Vec3 pos;
	Vec3 ornt;
	Vec3 vel;
	Vec3 ang;
	float size;
	IndexedTriangleList<Vertex> triangles;
	bool collisionFlag = false;
	bool moved = true;
	bool destroyed = false;
	float boundingRadius;
};