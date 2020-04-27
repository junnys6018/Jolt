#include <string>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <thread>

#include "MeshInternal.h"
#include "../Core/ProgressBar.h"
#include "../Core/StringUtility.h"

static inline bool IsSpace(char c)
{
	return c == ' ' || c == '\t';
}

static inline void GetFloat(float& f, const char** token)
{
	char* end;
	f = std::strtof(*token, &end);
	*token = end;
}

static inline void GetFloat3(float& x, float& y, float& z, const char** token)
{
	GetFloat(x, token);
	GetFloat(y, token);
	GetFloat(z, token);
}

static inline void GetFloat2(float& x, float& y, const char** token)
{
	GetFloat(x, token);
	GetFloat(y, token);
}

static void GetIndices(int& v, int& vn, int& vt, const char** token)
{
	vn = 1; vt = 1;
	v = atoi(*token);
	*token += strcspn(*token, "/ \t\r");
	if ((*token)[0] != '/')
		return;

	(*token)++;

	// i//k
	if ((*token)[0] == '/') 
	{
    	(*token)++;
    	vn = atoi(*token);
    	*token += strcspn(*token, "/ \t\r");
		return;
	}

	// i/j/k or i/j
	vt = atoi(*token);
	*token += strcspn(*token, "/ \t\r");
	if ((*token)[0] != '/')
		return;


	// i/j/k
  	(*token)++;  // skip '/'
	vn = atoi(*token);

	*token += strcspn(*token, "/ \t\r");
}

void BufferObj(const char* filepath, std::vector<vec3>& vPos, std::vector<vec3>& vNorm, std::vector<vec2>& vTex, std::vector<Index>& iBuf, ModelFlags& modelFlags)
{
	std::ifstream file(filepath);

	file.seekg(0, std::ios_base::end);
	auto size = file.tellg();
	file.seekg(0, std::ios_base::beg);

	double progress = 0.0;
	std::thread th(bar, &progress, "Loading File");

	std::string line;

	bool first_face = true;
	int iterations = 0;
	unsigned int fIndex = 0; // points to 1 off the last index
	while (iterations++, std::getline(file, line))
	{
		if (iterations % 1000 == 0)
		{
			auto pos = file.tellg();
			progress = (double)pos / (int)size;
		}

		// Skip leading space
		const char* token = line.c_str();
		token += std::strspn(token, " \t");

		assert(token);
    	if (token[0] == '\0') continue;  // empty line

    	if (token[0] == '#') continue;  // comment line

		if (token[0] == 'v' && IsSpace(token[1]))
		{
			token += 2;
			float x, y, z;
			GetFloat3(x, y, z, &token);
			vPos.push_back({ x, y, z });
		}
		else if (token[0] == 'v' && token[1] == 'n' && IsSpace((token[2])))
		{
			token += 3;
			float x, y, z;
			GetFloat3(x, y, z, &token);
			vNorm.push_back({ x, y, z });
		}
		else if (token[0] == 'v' && token[1] == 't' && IsSpace((token[2])))
		{
			token += 3;
			float x, y;
			GetFloat2(x, y, &token);
			vTex.push_back({ x, y });
		}
		else if (token[0] == 'f' && IsSpace(token[1]))
		{
			token += 2;
			if (first_face)
			{
				first_face = false;
				modelFlags = ModelFlagsPosition;
				if (vNorm.size() != 0)
					modelFlags |= ModelFlagsNormal;
				if (vTex.size() != 0)
					modelFlags |= ModelFlagsTextureCoordinate;
			}

			int iterations = 0;
			TrimWhiteSpace(&token);
			while (token[0] != '\0' && token[0] != '\n' && token[0] != '\r')
			{
				int v, vt, vn;
				GetIndices(v, vn, vt, &token);
				iBuf.push_back({ v - 1, vt - 1, vn - 1 });
				iterations++;
				TrimWhiteSpace(&token);
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
	progress = 1.0;
	th.join();
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
