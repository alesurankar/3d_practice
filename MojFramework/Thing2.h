#pragma once
#include "Drawable.h"
#include "Sphere.h"
#include "NDCScreenTransformer.h"
#include "Graphics.h"
#include "Vec3.h"
#include "Mat.h"
#include "Pipeline.h"
#include "SceneEffect.h"
#include <memory>

class Thing2
{
public:
	using Effect = SceneEffect;
	using Pipeline = Pipeline<Effect>;
	Thing2(Graphics& gfx, const Vec3& pos_in, IndexedTriangleList<SceneVertex> tl, float size = 1.0f);
	void Move(float x, float y, float z);
	void Move(float dt);
	void Rotate(float x, float y, float z);
	void Rotate(float dt);
	Vec3 GetPos() const;
	Vec3 GetOrnt() const;
	const IndexedTriangleList<SceneVertex>& GetTriangle() const;
	void SetVelocity(float vx, float vy, float vz);
	void ChangeVelocity();
	void SetTorque(float roll, float pitch, float yaw);
	void ChangeTorque();
	BoxF GetWorldBoundingBox() const;
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
	Vec3 torq;
	float size;
	IndexedTriangleList<SceneVertex> itlist;
	IndexedTriangleList<SceneVertex> triangles;
	bool collisionFlag = false;
	bool moved = true;
	bool destroyed = false;
};