template<class Vertex>
class DefaultVertexShader
{
public:
    typedef Vertex Output;

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
    Output operator()(const Vertex& v) const
    {
        const Vec4 p4(v.pos, 1.0f);
        const Vec4 transformed = p4 * worldProj;

        const Vec3 ndc(transformed.x / transformed.w,
            transformed.y / transformed.w,
            transformed.z / transformed.w);
        return Output(ndc, v);
    }

private:
    Mat4 world = Mat4::Identity();
    Mat4 proj = Mat4::Identity();
    Mat4 worldProj = Mat4::Identity();
};
