#pragma once	
#include <vector>

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

struct Vertex
{
	vec3 position;
	vec2 texCoord;
	vec3 normal;
	Vertex(vec3 pos, vec2 tex, vec3 norm)
		:position(pos), texCoord(tex), normal(norm) {}
};


void BufferObj(const char* filepath, 
			   std::vector<vec3>& vPos, 
			   std::vector<vec3>& vNorm, 
			   std::vector<vec2>& vTex, 
			   std::vector<Index>& iBuf);

void ExpandObj(std::vector<vec3>& vPos,
			   std::vector<vec3>& vNorm,
			   std::vector<vec2>& vTex,
			   std::vector<Index>& iBuf,
			   std::vector<Vertex>& vertexBuffer,
			   std::vector<unsigned int>& indexBuffer);

void WriteToFile(const std::string& filename,
				 const std::vector<Vertex>& vertexBuffer,
				 const std::vector<unsigned>& indexBuffer);

