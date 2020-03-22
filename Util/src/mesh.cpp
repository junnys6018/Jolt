#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "mesh.h"

void BufferObj(const char* filepath, std::vector<vec3>& vPos, std::vector<vec3>& vNorm, std::vector<vec2>& vTex, std::vector<Index>& iBuf, ModelFlags& modelFlags)
{
	std::ifstream file(filepath);
	std::string line;

	bool first_face = true;
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
			if (first_face)
			{
				first_face = false;
				modelFlags = ModelFlagsPosition;
				if (vNorm.size() != 0)
					modelFlags |= ModelFlagsNormal;
				if (vTex.size() != 0)
					modelFlags |= ModelFlagsTextureCoordinate;
			}
			std::string data;
			int iterations = 0;
			while (s >> data)
			{
				int v, vt, vn;
				if ((modelFlags & ModelFlagsNormal) && (modelFlags & ModelFlagsTextureCoordinate))
				{
					std::sscanf(data.c_str(), "%i/%i/%i", &v, &vt, &vn);
				}
				else if (modelFlags & ModelFlagsNormal)
				{
					vt = 1;
					std::sscanf(data.c_str(), "%i//%i", &v, &vn);
				}
				else if (modelFlags & ModelFlagsTextureCoordinate)
				{
					vn = 1;
					std::sscanf(data.c_str(), "%i/%i", &v, &vt);
				}
				else
				{
					vn = 1; vt = 1;
					std::sscanf(data.c_str(), "%i", &v);
				}
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

void ExpandObj(std::vector<vec3>& vPos, std::vector<vec3>& vNorm, std::vector<vec2>& vTex, std::vector<Index>& iBuf,
	std::vector<float>& vertexBuffer, std::vector<unsigned int>& indexBuffer, const ModelFlags modelFlags)
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

			vertexBuffer.emplace_back(vPos[vIndex].x);
			vertexBuffer.emplace_back(vPos[vIndex].y);
			vertexBuffer.emplace_back(vPos[vIndex].z);

			if (modelFlags & ModelFlagsTextureCoordinate)
			{
				vertexBuffer.emplace_back(vTex[vtIndex].x);
				vertexBuffer.emplace_back(vTex[vtIndex].y);
			}

			if (modelFlags & ModelFlagsNormal)
			{
				vertexBuffer.emplace_back(vNorm[vnIndex].x);
				vertexBuffer.emplace_back(vNorm[vnIndex].y);
				vertexBuffer.emplace_back(vNorm[vnIndex].z);
			}

			indexBuffer.emplace_back(last_index);
			map.insert(std::make_pair(index, last_index));
			++last_index;
		}
		else
			indexBuffer.emplace_back(map[index]);
	}
}

void WriteToFile(const std::string& filename, const std::vector<float>& vertexBuffer,
	const std::vector<unsigned>& indexBuffer, const ModelFlags modelFlags)
{
	std::ofstream file(filename, std::ios::binary);
	// Header
	struct
	{
		// { pos, tex, norm }
		char vertex_attribs[3] = { 'y','n','n' };
		std::size_t vertex_buffer_size;
		std::size_t index_count;
	} header;

	if (modelFlags & ModelFlagsTextureCoordinate)
		header.vertex_attribs[1] = 'y';
	if (modelFlags & ModelFlagsNormal)
		header.vertex_attribs[2] = 'y';

	header.vertex_buffer_size = vertexBuffer.size();
	header.index_count = indexBuffer.size();

	file.write((char*)& header, sizeof(header));

	// Body
	file.write((char*)vertexBuffer.data(), sizeof(float) * vertexBuffer.size());
	file.write((char*)indexBuffer.data(), sizeof(unsigned) * indexBuffer.size());

	file.close();
}
