#pragma once
#include "Pipeline.h"
#include "BaseVertexShader.h"
#include "DefaultGeometryShader.h"
#include "BasePhongShader.h"


class VertexLightTexturedEffect
{
public:
	class Vertex
	{
	public:
		Vertex() = default;
		Vertex(const Vec4& pos)
			:
			pos(pos)
		{
		}
		Vertex(const Vec4& pos, const Vertex& src)
			:
			n(src.n),
			pos(pos)
		{
		}
		Vertex(const Vec4& pos, const Vec3& n)
			:
			n(n),
			pos(pos)
		{
		}
	public:
		Vec4 pos;
		Vec3 n;
		Vec2 t;
	};

	class VSOutput
	{
	public:
		VSOutput() = default;
		VSOutput(const Vec4& pos)
			:
			pos(pos)
		{
		}
		VSOutput(const Vec4& pos, const VSOutput& src)
			:
			t(src.t),
			l(src.l),
			pos(pos)
		{
		}
		VSOutput(const Vec4& pos, const Vec2& t, const Vec3& l)
			:
			t(t),
			pos(pos),
			l(l)
		{
		}
		VSOutput& operator+=(const VSOutput& rhs)
		{
			pos += rhs.pos;
			t += rhs.t;
			l += rhs.l;
			return *this;
		}
		VSOutput operator+(const VSOutput& rhs) const
		{
			return VSOutput(*this) += rhs;
		}
		VSOutput& operator-=(const VSOutput& rhs)
		{
			pos -= rhs.pos;
			t -= rhs.t;
			l -= rhs.l;
			return *this;
		}
		VSOutput operator-(const VSOutput& rhs) const
		{
			return VSOutput(*this) -= rhs;
		}
		VSOutput& operator*=(float rhs)
		{
			pos *= rhs;
			t *= rhs;
			l *= rhs;
			return *this;
		}
		VSOutput operator*(float rhs) const
		{
			return VSOutput(*this) *= rhs;
		}
		VSOutput& operator/=(float rhs)
		{
			pos /= rhs;
			t /= rhs;
			l /= rhs;
			return *this;
		}
		VSOutput operator/(float rhs) const
		{
			return VSOutput(*this) /= rhs;
		}
	public:
		Vec4 pos;
		Vec2 t;
		Vec3 l;
	};

	class VertexShader : public BaseVertexShader<VSOutput>
	{
	public:
		using Output = VSOutput;
	public:
		Output operator()(const Vertex& v) const
		{
			// world position
			const Vec4 worldPos = v.pos * world;

			// light vector (world space)
			const Vec3 v_to_l = Vec3(light_pos - worldPos);
			const float dist = v_to_l.Len();
			const Vec3 dir = v_to_l / dist;

			// attenuation
			const float attenuation =
				1.0f / (constant_attenuation +
					linear_attenuation * dist +
					quadradic_attenuation * dist * dist);

			// diffuse lighting
			const Vec3 d = light_diffuse * attenuation * std::max(0.0f, static_cast<Vec3>(Vec4(v.n, 0.0f) * worldView) * dir);
			const Vec3 l = d + light_ambient;
			const Vec4 p = Vec4(v.pos.x, v.pos.y, v.pos.z, 1.0f);
			
			return { p * worldViewProj, v.t, l };
		}
		void SetDiffuseLight(const Vec3& c)
		{
			light_diffuse = c;
		}
		void SetAmbientLight(const Vec3& c)
		{
			light_ambient = c;
		}
		void SetLightPosition(const Vec3& pos_in)
		{
			light_pos = pos_in;
		}
	private:
		Vec4 light_pos = { 0.0f,0.0f,0.5f,1.0f };
		Vec3 light_diffuse = { 1.0f,1.0f,1.0f };
		Vec3 light_ambient = { 0.2f,0.2f,0.2f };
		float linear_attenuation = 2.0f;
		float quadradic_attenuation = 2.619f;
		float constant_attenuation = 0.682f;
	};

	typedef DefaultGeometryShader<VertexShader::Output> GeometryShader;

	class PixelShader
	{
	public:
		template<class Input>
		Color operator()(const Input& in) const
		{
			const Vec3 materialColor = Vec3(pTex->GetPixel(
				(unsigned int)std::min(in.t.x * tex_width + 0.5f, tex_xclamp),
				(unsigned int)std::min(in.t.y * tex_height + 0.5f, tex_yclamp)
			)) / 255.0f;

			Vec3 tint = { 0.9f, 0.9f, 0.9f };
			Vec3 texColor = materialColor.GetHadamard(in.l).GetHadamard(tint).GetSaturated() * 255.0f;
			
			return Color(texColor);
		}
		void BindTexture(const Surface& tex)
		{
			pTex = &tex;
			tex_width = pTex->GetWidth();
			tex_height = pTex->GetHeight();
			tex_xclamp = tex_width - 1.0f;
			tex_yclamp = tex_height - 1.0f;
		}
	private:
		const Surface* pTex = nullptr;
		unsigned int tex_width;
		unsigned int tex_height;
		float tex_xclamp;
		float tex_yclamp;
	};
public:
	VertexShader vs;
	GeometryShader gs;
	PixelShader ps;
};
