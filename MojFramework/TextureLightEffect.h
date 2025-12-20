#pragma once
#include "Pipeline.h"
#include "DefaultGeometryShader.h"

class TextureLightEffect
{
public:
    class Vertex
    {
    public:
        Vec4 pos;
        Vec3 n;
        Vec2 t;

        Vertex() = default;

        Vertex(const Vec3& pos3, const Vec3& normal, const Vec2& tex)
            : pos(pos3, 1.0f), n(normal), t(tex) {
        }

        Vertex(const Vec4& pos4, const Vertex& src)
            : pos(pos4), n(src.n), t(src.t) {
        }

        Vertex& operator+=(const Vertex& rhs)
        {
            pos += rhs.pos;
            n += rhs.n;
            t += rhs.t;
            return *this;
        }
        Vertex operator+(const Vertex& rhs) const { return Vertex(*this) += rhs; }
        Vertex operator*(float s) const { return { pos * s, n * s, t * s }; }
    };

    class VertexShader
    {
    public:
        class Output
        {
        public:
            Vec4 pos;
            Vec2 t;
            Color color;

            Output() = default;

            Output& operator+=(const Output& rhs)
            {
                pos += rhs.pos;
                t += rhs.t;
                Vec3 c(color), c2(rhs.color);
                color = Color(c + c2);
                return *this;
            }

            Output operator+(const Output& rhs) const { return Output(*this) += rhs; }

            Output& operator-=(const Output& rhs)
            {
                pos -= rhs.pos;
                t -= rhs.t;
                Vec3 c(color), c2(rhs.color);
                color = Color(c - c2);
                return *this;
            }

            Output operator-(const Output& rhs) const { return Output(*this) -= rhs; }

            Output& operator*=(float s)
            {
                pos *= s;
                t *= s;
                Vec3 c(color);
                color = Color(c * s);
                return *this;
            }

            Output operator*(float s) const { return Output(*this) *= s; }

            Output& operator/=(float s)
            {
                pos /= s;
                t /= s;
                Vec3 c(color);
                color = Color(c / s);
                return *this;
            }

            Output operator/(float s) const { return Output(*this) /= s; }
        };

        void BindWorld(const Mat4& world_in)
        {
            world = world_in;
            worldProj = world * proj;
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

            // Transform normal using the upper-left 3x3 rotation part of the world matrix
            Vec3 nWorld = {
                v.n.x * world.elements[0][0] + v.n.y * world.elements[1][0] + v.n.z * world.elements[2][0],
                v.n.x * world.elements[0][1] + v.n.y * world.elements[1][1] + v.n.z * world.elements[2][1],
                v.n.x * world.elements[0][2] + v.n.y * world.elements[1][2] + v.n.z * world.elements[2][2]
            };
            nWorld = nWorld.GetNormalized();

            // Simple diffuse + ambient lighting
            float intensity = std::max(0.0f, nWorld * -lightDir);
            Vec3 lit = (ambient + diffuse * intensity).GetHadamard(materialColor).Saturate();

            // Output
            Output out;
            out.pos = clipPos;
            out.t = v.t;
            out.color = Color(lit * 255.0f);
            return out;
        }

        void SetLightDirection(const Vec3& d) { lightDir = d.GetNormalized(); }
        void SetMaterialColor(Color c) { materialColor = Vec3(c); }
        void SetDiffuseLight(const Vec3& c) { diffuse = c; }
        void SetAmbientLight(const Vec3& c) { ambient = c; }

    private:
        Mat4 world = Mat4::Identity();
        Mat4 proj = Mat4::Identity();
        Mat4 worldProj = Mat4::Identity();
        Vec3 lightDir = { 0.0f, 0.0f, 1.0f };
        Vec3 diffuse = { 1.0f, 1.0f, 1.0f };
        Vec3 ambient = { 0.1f, 0.1f, 0.1f };
        Vec3 materialColor = { 0.8f, 0.85f, 1.0f };
    };

    using GeometryShader = DefaultGeometryShader<VertexShader::Output>;

    class PixelShader
    {
    public:
        template<class Input>
        Color operator()(const Input& in) const
        {
            Color tex = pTex->GetPixel(
                (unsigned int)std::min(in.t.x * tex_width + 0.5f, tex_xclamp),
                (unsigned)std::min(in.t.y * texH + 0.5f, texH - 1)
            );
            return tex * Vec3(in.color);
        }

        void BindTexture(const Surface& tex)
        {
            pTex = &tex;
            texW = float(tex.GetWidth());
            texH = float(tex.GetHeight());
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
