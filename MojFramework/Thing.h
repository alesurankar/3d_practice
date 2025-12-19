#pragma once
#include "Drawable.h"
#include "NDCScreenTransformer.h"
#include "Graphics.h"
#include "Vec3.h"
#include "Mat.h"
#include "Pipeline.h"
#include "TextureEffect.h"
#include <memory>

class Thing
{
public:
	typedef Pipeline<TextureEffect> Pipeline;
	typedef typename Pipeline::Vertex Vertex;
	Thing(Graphics& gfx, const Vec3& pos_in, const std::wstring& filename, float size = 1.0f);
	void Move(float x, float y, float z);
	void Move(float dt);
	void Rotate(float x, float y, float z);
	void Rotate(float dt);
	Vec3 GetPos() const;
	Vec3 GetOrnt() const;
	const IndexedTriangleList<Vertex>& GetTriangle() const;
	void SetVelocity(float vx, float vy, float vz);
	void ChangeVelocity();
	void SetTorque(float roll, float pitch, float yaw);
	void ChangeTorque();
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
	Vec3 torq;
	float size;
	std::shared_ptr<Surface> pTexture;
	IndexedTriangleList<Vertex> itlist;
	IndexedTriangleList<Vertex> triangles;
	bool collisionFlag = false;
	bool moved = true;
	bool destroyed = false;
};