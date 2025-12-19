#pragma once

template<class Vertex>
class DefaultVertexShader
{
public:
	typedef Vertex Output;
public:
	void BindTransformation(const Mat4& transformation_in)
	{
		transformation = transformation_in;
	}
	Output operator()(const Vertex& v) const
	{
		const Vec4 pt = Vec4(v.pos) * transformation;
		return Output(Vec3(pt.x, pt.y, pt.z), v);
	}
private:
	Mat4 transformation;
};