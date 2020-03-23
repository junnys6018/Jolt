#pragma once
#include "Rendering/OpenGL/VertexArray.h"
#include "Rendering/OpenGL/VertexBuffer.h"
#include "Rendering/OpenGL/IndexBuffer.h"

namespace Jolt
{
	struct Mesh
	{
	public:
		Mesh() = default;
		Mesh(VertexBuffer* VBuf, IndexBuffer* IBuf, VertexArray* VAO)
			:VertexBuffer(VBuf), IndexBuffer(IBuf), VertexArray(VAO)
		{

		}
		Mesh(Mesh& other)
			:VertexBuffer(other.VertexBuffer.release()), IndexBuffer(other.IndexBuffer.release()), VertexArray(other.VertexArray.release())
		{

		}

		std::unique_ptr<VertexBuffer> VertexBuffer;
		std::unique_ptr<IndexBuffer> IndexBuffer;
		std::unique_ptr<VertexArray> VertexArray;
	};
}