#pragma once
#include "Vec3.h"
#include "IndexedTriangleList.h"
#include "MyPipeline.h"
#include <vector>

class CubeMesh
{
public:
    CubeMesh(float size)
    {
        const float s = size / 2.0f;
        vertices = {
            {-s, -s, -s}, { s, -s, -s}, { s,  s, -s}, {-s,  s, -s}, // front
            {-s, -s,  s}, { s, -s,  s}, { s,  s,  s}, {-s,  s,  s}  // back
        };
    }

    IndexedTriangleList<MyPipeline::Vertex> GetTriangles() const
    {
        std::vector<MyPipeline::Vertex> verts;
        for (auto& v : vertices)
        {
            verts.emplace_back(v); // default color will be white
        }

        std::vector<size_t> indices = {
            0,2,1, 0,3,2, // front
            4,5,6, 4,6,7, // back
            0,1,5, 0,5,4, // bottom
            2,3,7, 2,7,6, // top
            0,4,7, 0,7,3, // left
            1,2,6, 1,6,5  // right
        };

        return { verts, indices };
    }

private:
    std::vector<Vec3> vertices;
};
