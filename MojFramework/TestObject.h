//#pragma once
//#include "Squere.h"
//#include "NDCScreenTransformer.h"
//#include "Graphics.h"
//#include "Vec3.h"
//#include "Mat.h"
//#include "Pipeline.h"
//#include "TextureEffect.h"
//#include <memory>
//
//class TestObject
//{
//public:
//	typedef Pipeline<TextureEffect> Pipeline;
//	typedef typename Pipeline::Vertex Vertex;
//	TestObject(Graphics& gfx, const Vec3& pos_in, const std::wstring& filename);
//	void Move(float x, float y, float z);
//	void Move();
//	void Rotate(float x, float y, float z);
//	void Rotate();
//	Vec3 GetPos() const;
//	Vec3 GetOrnt() const;
//	const IndexedTriangleList<Vertex>& GetTriangle() const;
//	void SetVelocity(float vx, float vy, float vz);
//	void ChangeVelocity();
//	void SetTorque(float roll, float pitch, float yaw);
//	void ChangeTorque();
//	BoxF GetWorldBoundingBox() const;
//	const Surface& GetTexture() const;
//	void SetCollisionFlag();
//	void ResetCollisionFlag();
//	bool CheckCollisionFlag();
//	void SetMoved();
//	void ResetMoved();
//	bool CheckMoved();
//private:
//	void CheckBorder();
//private:
//	Vec3 pos;
//	Vec3 ornt;
//	Vec3 vel;
//	Vec3 torq;
//	std::shared_ptr<Surface> pTexture;
//	IndexedTriangleList<Vertex> itlist;
//	IndexedTriangleList<Vertex> triangles;
//	bool collisionFlag = false;
//	bool moved = true;
//};