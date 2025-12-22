#pragma once

template<class Vertex>
class BaseVertexShader
{
public:
	typedef Vertex Output;
public:

	void BindWorld(const Mat4& w)
	{
		world = w;
		UpdateDerived();
	}

	void BindView(const Mat4& v)
	{
		view = v;
		UpdateDerived();
	}

	void BindProjection(const Mat4& p)
	{
		proj = p;
		UpdateDerived();
	}
	const Mat4& GetProj() const
	{
		return proj;
	}
protected:
	void UpdateDerived()
	{
		worldView = world * view;
		worldViewProj = worldView * proj;
	}
protected:
	Mat4 world = Mat4::Identity();
	Mat4 view = Mat4::Identity();
	Mat4 proj = Mat4::Identity();

	Mat4 worldView = Mat4::Identity();
	Mat4 worldViewProj = Mat4::Identity();
};