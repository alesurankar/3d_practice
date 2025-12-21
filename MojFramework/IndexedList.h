#pragma once
#include <vector>
#include "Vec3.h"
#include <utility>
#include <cassert>
#include "tiny_obj_loader.h"
#include "Miniball.h"
#include <fstream>
#include <cctype>
#include <sstream>

template<class T>
class IndexedTriangleList
{
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(std::vector<T> verts_in, std::vector<size_t> indices_in)
		:
		vert(std::move(verts_in)),
		ind(std::move(indices_in))
	{
		assert(vert.size() > 2);
		assert(ind.size() % 3 == 0);
	}
	static IndexedTriangleList<T> Load(const std::string& filename)
	{
		IndexedTriangleList<T> tl;

		// check first line of file to see if CCW winding comment exists
		bool isCCW = false;
		{
			std::ifstream file(filename);
			std::string firstline;
			std::getline(file, firstline);
			std::transform(firstline.begin(), firstline.end(), firstline.begin(), [](char c) { return static_cast<char>(std::tolower(c)); });
			if (firstline.find("ccw") != std::string::npos)
			{
				isCCW = true;
			}
		}

		// these will be filled by obj loading function
		using namespace tinyobj;
		attrib_t attrib;
		std::vector<shape_t> shapes;
		std::string err;

		// load/parse the obj file
		const bool ret = LoadObj(&attrib, &shapes, nullptr, &err, filename.c_str());

		// check for errors
		if (!err.empty() && err.substr(0, 4) != "WARN")
		{
			throw std::runtime_error(("LoadObj returned error:" + err + " File:" + filename).c_str());
		}
		if (!ret)
		{
			throw std::runtime_error(("LoadObj returned false  File:" + filename).c_str());
		}
		if (shapes.size() == 0u)
		{
			throw std::runtime_error(("LoadObj object file had no shapes  File:" + filename).c_str());
		}

		// extract vertex data
		tl.vert.reserve(attrib.vertices.size() / 3u);
		for (int i = 0; i < attrib.vertices.size(); i += 3)
		{
			tl.vert.emplace_back(Vec3{
				attrib.vertices[i + 0],
				attrib.vertices[i + 1],
				attrib.vertices[i + 2]
				});
		}

		// extract index data
		const auto& mesh = shapes[0].mesh;
		tl.ind.reserve(mesh.indices.size());
		for (size_t f = 0; f < mesh.num_face_vertices.size(); f++)
		{
			if (mesh.num_face_vertices[f] != 3u)
			{
				std::stringstream ss;
				ss << "LoadObj error face #" << f << " has "
					<< mesh.num_face_vertices[f] << " vertices";
				throw std::runtime_error(ss.str().c_str());
			}

			for (size_t vn = 0; vn < 3u; vn++)
			{
				const auto idx = mesh.indices[f * 3u + vn];
				tl.ind.push_back(size_t(idx.vertex_index));
			}

			// reverse winding if file marked as CCW
			if (isCCW)
			{
				std::swap(tl.ind.back(), *std::prev(tl.ind.end(), 2));
			}
		}

		return tl;
	}
	void AdjustToTrueCenter()
	{
		// used to enable miniball to access vertex pos info
		struct VertexAccessor
		{
			typedef std::vector<T>::const_iterator Pit;
			typedef const float* Cit;
			Cit operator()(Pit it) const
			{
				return &it->pos.x;
			}
		};

		// solve the minimum bounding sphere
		Miniball::Miniball<VertexAccessor> mb(3, vert.cbegin(), vert.cend());
		// result is a pointer to float[3] (what a shitty fuckin interface)
		const auto pc = mb.center();
		const Vec3 center = { *pc,*std::next(pc),*std::next(pc,2) };
		// adjust all vertices so that center of minimal sphere is at 0,0
		for (auto& v : vert)
		{
			v.pos -= center;
		}
	}
	float GetRadius() const
	{
		return std::max_element(vert.begin(), vert.end(),
			[](const T& v0, const T& v1)
			{
				return v0.pos.LenSq() < v1.pos.LenSq();
			}
		)->pos.Len();
	}
	std::vector<T> vert;
	std::vector<size_t> ind;
};
