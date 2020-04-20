#pragma once	
#include <vector>
#include <string>

#define BIT(x) 1 << x

typedef int ModelFlags;
enum ModelFlags_
{
	ModelFlagsPosition = 0,
	ModelFlagsNormal = BIT(0),
	ModelFlagsTextureCoordinate = BIT(1)
};

struct vec3
{
	float x, y, z;
};

struct vec2
{
	float x, y;
};

struct Index
{
	int v, vt, vn;
	friend bool operator==(const Index& l, const Index& r)
	{
		return l.v == r.v && l.vn == r.vn && l.vt == r.vt;
	}
};

// Inject Hash
namespace std
{
	template<> struct hash<Index>
	{
		std::size_t operator()(Index const& index) const noexcept
		{
			std::size_t h1 = std::hash<int>{}(index.v);
			std::size_t h2 = std::hash<int>{}(index.vt);
			std::size_t h3 = std::hash<int>{}(index.vn);
			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};
}

void BufferObj(const char* filepath, 
			   std::vector<vec3>& vPos, 
			   std::vector<vec3>& vNorm, 
			   std::vector<vec2>& vTex, 
			   std::vector<Index>& iBuf,
			   ModelFlags& modelFlags);

void ExpandObj(std::vector<vec3>& vPos,
			   std::vector<vec3>& vNorm,
			   std::vector<vec2>& vTex,
			   std::vector<Index>& iBuf,
			   std::vector<float>& vertexBuffer,
			   std::vector<unsigned int>& indexBuffer,
			   const ModelFlags modelFlags);

void WriteToFile(const std::string& filename,
	             const std::vector<float>& vertexBuffer,
	             const std::vector<unsigned>& indexBuffer,
	             const ModelFlags modelFlags);

