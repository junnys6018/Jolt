#include "pch.h"
#include "MeshLoader.h"
#include <fstream>
namespace Jolt
{
	Mesh CreateFromFile(const std::string& filepath)
	{
		std::ifstream file(filepath, std::ios::binary);

		struct
		{
			std::size_t vertex_count;
			std::size_t index_count;
		} header;

		file.read((char*)& header, sizeof(header));
		float* vertices = new float[header.vertex_count * (3 + 3 + 2)];
		unsigned int* indices = new unsigned int[header.index_count];

		file.read((char*)vertices, header.vertex_count * (3 + 3 + 2) * sizeof(float));
		file.read((char*)indices, header.index_count * sizeof(unsigned));

		file.close();

		auto VAO = VertexArray::Create();
		VAO->Bind();

		auto VBuf = VertexBuffer::Create(header.vertex_count * (3 + 3 + 2) * sizeof(float), vertices);
		VBuf->Bind();
		VertexLayout layout = { 3,3,2 };
		VAO->SetVertexLayout(layout);

		auto IBuf = IndexBuffer::Create((GLsizei)header.index_count, indices);
		IBuf->Bind();

		return Mesh(VBuf, IBuf, VAO);
	}
}