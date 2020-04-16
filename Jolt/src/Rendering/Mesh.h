#pragma once
#include "pch.h"
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
			:m_VertexBuffer(VBuf), m_IndexBuffer(IBuf), m_VertexArray(VAO)
		{

		}

		Mesh(Mesh&& other) noexcept
			:m_VertexBuffer(other.m_VertexBuffer.release()), m_IndexBuffer(other.m_IndexBuffer.release()), m_VertexArray(other.m_VertexArray.release())
		{

		}

		Mesh& operator=(Mesh&& other) noexcept
		{
			m_VertexBuffer.reset(other.m_VertexBuffer.release());
			m_IndexBuffer.reset(other.m_IndexBuffer.release());
			m_VertexArray.reset(other.m_VertexArray.release());
		}

		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
	};
}