//#pragma once
//#include "Pipeline.h"
//#include "DefaultVertexShader.h"
//#include "DefaultGeometryShader.h"
//#include <memory>
//
//// basic texture effect
//class TextureEffect
//{
//public:
//    class Vertex
//    {
//    public:
//        Vertex() = default;
//        Vertex(const Vec3& pos3)
//            :
//            pos(pos3, 1.0f)
//        {
//        }
//        Vertex(const Vec4& pos4)
//            :
//            pos(pos4)
//        {
//        }
//        Vertex(const Vec3& pos3, const Vertex& src)
//            :
//            pos(pos3, 1.0f),
//            n(src.n),
//            t(src.t)
//        {
//        }
//        Vertex(const Vec4& pos4, const Vertex& src)
//            :
//            pos(pos4),
//            n(src.n),
//            t(src.t)
//        {
//        }
//        Vertex(const Vec4& pos4, const Vec3& normal, const Vec2& t)
//            :
//            pos(pos4),
//            n(normal),
//            t(t)
//        {
//        }
//        Vertex& operator+=(const Vertex& rhs)
//        {
//            pos += rhs.pos;
//            n += rhs.n;
//            t += rhs.t;
//            return *this;
//        }
//        Vertex operator+(const Vertex& rhs) const
//        {
//            return Vertex(*this) += rhs;
//        }
//        Vertex& operator-=(const Vertex& rhs)
//        {
//            pos -= rhs.pos;
//            n -= rhs.n;
//            t -= rhs.t;
//            return *this;
//        }
//        Vertex operator-(const Vertex& rhs) const
//        {
//            return Vertex(*this) -= rhs;
//        }
//        Vertex& operator*=(float rhs)
//        {
//            pos *= rhs;
//            n *= rhs;
//            t *= rhs;
//            return *this;
//        }
//        Vertex operator*(float rhs) const
//        {
//            return Vertex(*this) *= rhs;
//        }
//        Vertex& operator/=(float rhs)
//        {
//            pos /= rhs;
//            n /= rhs;
//            t /= rhs;
//            return *this;
//        }
//        Vertex operator/(float rhs) const
//        {
//            return Vertex(*this) /= rhs;
//        }
//    public:
//        Vec4 pos;
//        Vec3 n;
//        Vec2 t;
//    };
//
//    class VertexShader
//    {
//    public:
//        using Output = Vertex;
//        void BindWorld(const Mat4& world_in)
//        {
//            world = world_in;
//            worldProj = world * proj;
//        }
//        void BindProjection(const Mat4& proj_in)
//        {
//            proj = proj_in;
//            worldProj = world * proj;
//        }
//        const Mat4& GetProj() const
//        {
//            return proj;
//        }
//        Output operator()(const Vertex& v) const
//        {
//            Vec4 clipPos = v.pos * worldProj;
//    
//            return Output(clipPos, v);
//        }
//    private:
//        Mat4 world = Mat4::Identity();
//        Mat4 proj = Mat4::Identity();
//        Mat4 worldProj = Mat4::Identity();
//    };
//
//	typedef DefaultGeometryShader<VertexShader::Output> GeometryShader;
//
//	class PixelShader
//	{
//	public:
//		template<class Input>
//		Color operator()(const Input& in) const
//		{
//			Color texColor = pTex->GetPixel(
//				(unsigned int)std::min(in.t.x * tex_width + 0.5f, tex_xclamp),
//				(unsigned int)std::min(in.t.y * tex_height + 0.5f, tex_yclamp)
//			);
//			Vec3 tint = { 0.9f, 0.9f, 0.9f };
//			return texColor * tint;
//        }
//		void BindTexture(const Surface& tex)
//		{
//			pTex = &tex;
//			tex_width = float(pTex->GetWidth());
//			tex_height = float(pTex->GetHeight());
//			tex_xclamp = tex_width - 1.0f;
//			tex_yclamp = tex_height - 1.0f;
//		}
//	private:
//		const Surface* pTex = nullptr;
//		float tex_width;
//		float tex_height;
//		float tex_xclamp;
//		float tex_yclamp;
//	};
//public:
//	VertexShader vs;
//	GeometryShader gs;
//	PixelShader ps;
//};