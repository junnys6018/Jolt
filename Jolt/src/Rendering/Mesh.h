#pragma once
#include "pch.h"
#include "Rendering/OpenGL/VertexArray.h"
#include "Rendering/OpenGL/VertexBuffer.h"
#include "Rendering/OpenGL/IndexBuffer.h"

namespace Jolt
{
	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(VertexBuffer* VBuf, IndexBuffer* IBuf, VertexArray* VAO)
			:m_VertexBuffer(std::move(*VBuf)), m_IndexBuffer(std::move(*IBuf)), m_VertexArray(std::move(*VAO))
		{

		}

		Mesh(Mesh&& other) noexcept
			:m_VertexBuffer(std::move(other.m_VertexBuffer)), m_IndexBuffer(std::move(other.m_IndexBuffer)), m_VertexArray(std::move(other.m_VertexArray))
		{

		}

		Mesh& operator=(Mesh&& other) noexcept
		{
			// Check for self assignment
			if (this != &other)
			{
				m_VertexBuffer = std::move(other.m_VertexBuffer);
				m_IndexBuffer = std::move(other.m_IndexBuffer);
				m_VertexArray = std::move(other.m_VertexArray);
			}
			return *this;
		}

		VertexBuffer m_VertexBuffer;
		IndexBuffer m_IndexBuffer;
		VertexArray m_VertexArray;
	};
}