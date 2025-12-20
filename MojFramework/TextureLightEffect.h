#pragma once
#include "Pipeline.h"
#include "DefaultGeometryShader.h"

class TextureLightEffect
{
public:
    class Vertex
    {
    public:

        Vertex() = default;
        Vertex(const Vec3& pos3, const Vec3& normal, const Vec2& tex)
            :
            pos(pos3, 1.0f),
            n(normal),
            t(tex)
        {
        }
        Vertex(const Vec4& pos4, const Vertex& src)
            :
            pos(pos4),
            n(src.n),
            t(src.t)
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

    class VertexShader
    {
    public:
        class Output
        {
        public:
            Output() = default;
            Output(const Vec4& pos_in)
                :
                pos(pos_in)
            {
            }
            Output(const Vec4& pos_in, const Output& src)
                :
                pos(pos_in),
                t(src.t),
                color(src.color)
            {
            }
            Output(const Vec4& pos_in, const Vec2& t_in, const Color& color_in)
                :
                pos(pos_in),
                t(t_in),
                color(color_in)
            {
            }
            Output& operator+=(const Output& rhs)
            {
                pos += rhs.pos;
                t += rhs.t;
                Vec3 c(color), c2(rhs.color);
                color = Color(c + c2);
                return *this;
            }
            Output operator+(const Output& rhs) const 
            { 
                return Output(*this) += rhs;
            }
            Output& operator-=(const Output& rhs)
            {
                pos -= rhs.pos;
                t -= rhs.t;
                Vec3 c(color), c2(rhs.color);
                color = Color(c - c2);
                return *this;
            }
            Output operator-(const Output& rhs) const 
            { 
                return Output(*this) -= rhs;
            }
            Output& operator*=(float rhs)
            {
                pos *= rhs;
                t *= rhs;
                Vec3 c(color);
                color = Color(c * rhs);
                return *this;
            }
            Output operator*(float rhs) const 
            { 
                return Output(*this) *= rhs;
            }
            Output& operator/=(float rhs)
            {
                pos /= rhs;
                t /= rhs;
                Vec3 c(color);
                color = Color(c / rhs);
                return *this;
            }
            Output operator/(float rhs) const
            { 
                return Output(*this) /= rhs;
            }
        public:
            Vec4 pos;
            Vec2 t;
            Color color;
        };
    public:
        void BindWorld(const Mat4& world_in)
        {
            world = world_in;
            //worldProj = world * proj;
        }
        void BindProjection(const Mat4& proj_in)
        {
            proj = proj_in;
            worldProj = world * proj;
        }
        const Mat4& GetProj() const
        {
            return proj;
        }
        Output operator()(const Vertex& v) const
        {
            // Transform vertex position to clip space
            Vec4 clipPos = v.pos * worldProj;

            Mat3 rotation;
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    rotation.elements[r][c] = world.elements[r][c];

            const auto d = diffuse * std::max(0.0f, -(v.n * rotation) * dir);
            const auto c = color.GetHadamard(d + ambient).Saturate() * 255.0f;
            return{ clipPos, v.t, Color(c) };
        }
        void SetDiffuseLight(const Vec3& c)
        {
            diffuse = { c.x,c.y,c.z };
        }
        void SetAmbientLight(const Vec3& c)
        {
            ambient = { c.x,c.y,c.z };
        }
        void SetLightDirection(const Vec3& dl)
        {
            assert(dl.LenSq() >= 0.001f);
            dir = dl.GetNormalized();
        }
        void SetMaterialColor(Color c)
        {
            color = Vec3(c);
        }
    private:
        Mat4 world = Mat4::Identity();
        Mat4 proj = Mat4::Identity();
        Mat4 worldProj = Mat4::Identity();
        Vec3 dir = { 0.0f, 0.0f, 1.0f };
        Vec3 diffuse = { 1.0f, 1.0f, 1.0f };
        Vec3 ambient = { 0.1f, 0.1f, 0.1f };
        Vec3 color = { 0.8f, 0.85f, 1.0f };
    };

    using GeometryShader = DefaultGeometryShader<VertexShader::Output>;

    class PixelShader
    {
    public:
        template<class Input>
        Color operator()(const Input& in) const
        {
            Color texColor = pTex->GetPixel(
                (unsigned int)std::min(in.t.x * texW + 0.5f, texW - 1.0f),
                (unsigned int)std::min(in.t.y * texH + 0.5f, texH - 1.0f)
            );
            return texColor *Vec3(in.color);
        }

        void BindTexture(const Surface& tex)
        {
            pTex = &tex;
            texW = float(pTex->GetWidth());
            texH = float(pTex->GetHeight());
        }

    private:
        const Surface* pTex = nullptr;
        float texW = 0;
        float texH = 0;
    };

public:
    VertexShader vs;
    GeometryShader gs;
    PixelShader ps;
};
