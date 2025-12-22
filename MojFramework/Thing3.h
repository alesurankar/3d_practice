#pragma once
#include "Squere.h"
#include "Sphere.h"
#include "NDCScreenTransformer.h"
#include "Graphics.h"
#include "Vec3.h"
#include "Mat.h"
#include "Pipeline.h"
#include "SceneEffect.h"
#include "Surface.h"
#include <memory>

class Thing3
{
public:
	using Effect = VertexLightTexturedEffect;
	using Pipeline = Pipeline<Effect>;
	Thing3(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<VertexLightTexturedVertex> tl, const std::wstring& filename, float size = 1.0f);
	void Move(float x, float y, float z);
	void Move(float dt);
	void Rotate(float x, float y, float z);
	void Rotate(float dt);
	Vec3 GetPos() const;
	Vec3 GetOrnt() const;
	const IndexedTriangleList<VertexLightTexturedVertex>& GetTriangle() const;
	void SetVelocity(float vx, float vy, float vz);
	void ChangeVelocity();
	void SetAngle(float roll, float pitch, float yaw);
	void ChangeAngle();
	BoxF GetWorldBoundingBox() const;
	const Surface& GetTexture() const;
	void SetCollisionFlag();
	void ResetCollisionFlag();
	bool CheckCollisionFlag();
	void SetMoved();
	void ResetMoved();
	bool CheckMoved();
private:
	void CheckBorder();
public:
	Vec3 pos;
	Vec3 ornt;
	Vec3 vel;
	Vec3 ang;
	std::shared_ptr<Surface> pTexture;
	float size;
	IndexedTriangleList<VertexLightTexturedVertex> itlist;
	IndexedTriangleList<VertexLightTexturedVertex> triangles;
	bool collisionFlag = false;
	bool moved = true;
	bool destroyed = false;
};