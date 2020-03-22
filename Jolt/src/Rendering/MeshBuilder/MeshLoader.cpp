#include "pch.h"
#include "MeshLoader.h"
#include <fstream>

#define TEX 1
#define NORM 2

namespace Jolt
{
	Mesh CreateFromFile(const std::string& filepath)
	{
		std::ifstream file(filepath, std::ios::binary);

		struct
		{
			char vertex_attribs[3];
			std::size_t vertex_buffer_size;
			std::size_t index_count;
		} header;

		file.read((char*)& header, sizeof(header));
		float* vertices = new float[header.vertex_buffer_size];
		unsigned int* indices = new unsigned int[header.index_count];

		file.read((char*)vertices, header.vertex_buffer_size * sizeof(float));
		file.read((char*)indices, header.index_count * sizeof(unsigned));

		file.close();

		auto VAO = VertexArray::Create();
		VAO->Bind();

		auto VBuf = VertexBuffer::Create(header.vertex_buffer_size * sizeof(float), vertices);
		VBuf->Bind();

		VertexLayout layout = { 3 };
		if (header.vertex_attribs[TEX] == 'y')
			layout.PushAttribute(2);
		if (header.vertex_attribs[NORM] == 'y')
			layout.PushAttribute(3);

		VAO->SetVertexLayout(layout);

		auto IBuf = IndexBuffer::Create((GLsizei)header.index_count, indices);
		IBuf->Bind();

		delete[] vertices;
		delete[] indices;

		return Mesh(VBuf, IBuf, VAO);
	}
}