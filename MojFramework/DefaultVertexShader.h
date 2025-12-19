template<class Vertex>
class DefaultVertexShader
{
public:
    using Output = Vertex;

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
        Vec4 clipPos = v.pos * worldProj;

        return Output(clipPos, v);
    }

private:
    Mat4 world = Mat4::Identity();
    Mat4 proj = Mat4::Identity();
    Mat4 worldProj = Mat4::Identity();
};
