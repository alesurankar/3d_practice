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
        Vertex(const Vec3& pos3)
            :
            pos(pos3, 1.0f)
        {
        }
        Vertex(const Vec4& pos4)
            :
            pos(pos4)
        {
        }
        Vertex(const Vec3& pos3, const Vertex& src)
            :
            pos(pos3, 1.0f),
            n(src.n),
            t(src.t)
        {
        }
        Vertex(const Vec4& pos4, const Vertex& src)
            :
            pos(pos4),
            n(src.n),
            t(src.t)
        {
        }
        Vertex(const Vec4& pos4, const Vec3& normal, const Vec2& t)
            :
            pos(pos4),
            n(normal),
            t(t)
        {
        }
        Vertex& operator+=(const Vertex& rhs)
        {
            pos += rhs.pos;
            n += rhs.n;
            t += rhs.t;
            return *this;
        }
        Vertex operator+(const Vertex& rhs) const
        {
            return Vertex(*this) += rhs;
        }
        Vertex& operator-=(const Vertex& rhs)
        {
            pos -= rhs.pos;
            n -= rhs.n;
            t -= rhs.t;
            return *this;
        }
        Vertex operator-(const Vertex& rhs) const
        {
            return Vertex(*this) -= rhs;
        }
        Vertex& operator*=(float rhs)
        {
            pos *= rhs;
            n *= rhs;
            t *= rhs;
            return *this;
        }
        Vertex operator*(float rhs) const
        {
            return Vertex(*this) *= rhs;
        }
        Vertex& operator/=(float rhs)
        {
            pos /= rhs;
            n /= rhs;
            t /= rhs;
            return *this;
        }
        Vertex operator/(float rhs) const
        {
            return Vertex(*this) /= rhs;
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

			// normal (world space)
			const Vec3 n_world = Vec3(Vec4(v.n, 0.0f) * world).GetNormalized();

			// attenuation
			const float attenuation =
				1.0f / (constant_attenuation +
					linear_attenuation * dist +
					quadradic_attenuation * dist * dist);

			// diffuse lighting
			const float ndotl = std::max(0.0f, n_world * dir);
			const Vec3 d = light_diffuse * attenuation * ndotl;

			const Vec3 l = d + light_ambient;

			return { v.pos * worldViewProj, v.t, l };
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
		Vec3 light_ambient = { 0.1f,0.1f,0.1f };
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
			Vec3 materialColor = Vec3(pTex->GetPixel(
				(unsigned int)std::min(in.t.x * tex_width + 0.5f, tex_xclamp),
				(unsigned int)std::min(in.t.y * tex_height + 0.5f, tex_yclamp)
			));

			Vec3 tint = { 0.9f, 0.9f, 0.9f };
			Vec3 texColor = materialColor.GetHadamard(in.l).GetHadamard(tint).GetSaturated();
			
			//return Color(texColor);
			//return Color(materialColor);
			return Color(255u, 0u, 0u);
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
