#include "pch.h"
#include "MeshLoader.h"
#include <fstream>

#define TEX 1
#define NORM 2

namespace Jolt
{
	Mesh CreateFromFile(const std::string& filepath, MeshMetaData* meta_data)
	{
		LOG_INFO("Loading Mesh: {}", filepath);
		std::ifstream file(filepath, std::ios::binary);
		JOLT_ASSERT(file.good(), "Failed to load:", filepath.c_str());

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

		if (meta_data != nullptr)
		{
			meta_data->m_VertexBufferSize = header.vertex_buffer_size;
			meta_data->m_IndexCount = header.index_count;
			meta_data->m_HasNormals = header.vertex_attribs[NORM] == 'y';
			meta_data->m_HasTexCoords = header.vertex_attribs[TEX] == 'y';
		}

		return Mesh(VBuf, IBuf, VAO);
	}
}