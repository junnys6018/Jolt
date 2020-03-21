#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "mesh.h"

void BufferObj(const char* filepath, std::vector<vec3>& vPos, std::vector<vec3>& vNorm, std::vector<vec2>& vTex, std::vector<Index>& iBuf)
{
	std::ifstream file(filepath);
	std::string line;

	unsigned int fIndex = 0; // points to 1 off the last index
	while (std::getline(file, line))
	{
		std::stringstream s(line);
		std::string id;
		s >> id;
		if (id == "v")
		{
			float x, y, z;
			s >> x; s >> y; s >> z;
			vPos.push_back({ x, y, z });
		}
		else if (id == "vn")
		{
			float x, y, z;
			s >> x; s >> y; s >> z;
			vNorm.push_back({ x, y, z });
		}
		else if (id == "vt")
		{
			float x, y;
			s >> x; s >> y;
			vTex.push_back({ x, y });
		}
		else if (id == "f")
		{
			std::string data;
			int iterations = 0;
			while (s >> data)
			{
				int v, vt, vn;
				std::sscanf(data.c_str(), "%i/%i/%i", &v, &vt, &vn);
				iBuf.push_back({ v - 1, vt - 1, vn - 1 });
				iterations++;
			}
			if (iterations == 4) // Rectangle was specified, assume points are specifed in ACW winding order
			{
				std::size_t begin = iBuf.size() - 4;
				Index i1 = iBuf[begin];
				Index i2 = iBuf[begin + 1];
				Index i3 = iBuf[begin + 2];
				Index i4 = iBuf[begin + 3];
				// reorder quad into 2 triangles
				iBuf[begin + 3] = i1;
				iBuf.push_back(i3);
				iBuf.push_back(i4);
				fIndex += 3; // extra triangle was added
			}
			fIndex += 3;
		}
	}
}

void ExpandObj(std::vector<vec3>& vPos, std::vector<vec3>& vNorm, std::vector<vec2>& vTex, std::vector<Index>& iBuf, std::vector<Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer)
{
	std::unordered_map<Index, unsigned int> map;
	unsigned int last_index = 0;
	for (auto index : iBuf)
	{
		if (map.find(index) == map.end())	// if no index exsists
		{
			// convert negative indices to positive
			unsigned int vIndex = index.v >= 0 ? index.v : vPos.size() + index.v + 1;
			unsigned int vtIndex = index.vt >= 0 ? index.vt : vTex.size() + index.vt + 1;
			unsigned int vnIndex = index.vn >= 0 ? index.vn : vNorm.size() + index.vn + 1;
			vertexBuffer.push_back({ vPos[vIndex], vTex[vtIndex], vNorm[vnIndex] });
			indexBuffer.emplace_back(last_index);
			map.insert(std::make_pair(index, last_index));
			++last_index;
		}
		else
			indexBuffer.emplace_back(map[index]);
	}
}

void WriteToFile(const std::string& filename, const std::vector<Vertex>& vertexBuffer, const std::vector<unsigned>& indexBuffer)
{
	std::ofstream file(filename, std::ios::binary);
	// Header
	std::size_t size = vertexBuffer.size();
	file.write((char*)&size, sizeof(std::size_t));
	size = indexBuffer.size();
	file.write((char*)&size, sizeof(std::size_t));

	// Body
	file.write((char*)vertexBuffer.data(), sizeof(Vertex) * vertexBuffer.size());
	file.write((char*)indexBuffer.data(), sizeof(unsigned) * indexBuffer.size());

	file.close();
}
