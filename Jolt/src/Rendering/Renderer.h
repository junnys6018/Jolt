#pragma once
#include "Camera/Camera.h"
#include "OpenGL/Shader.h"

#include "DrawData.h"

#include <glad/glad.h>

namespace Jolt
{
	class Renderer
	{
	public:
		template<typename Light>
		static void BeginScene(Light light, Shader* shader, Camera camera)
		{
			JOLT_ASSERT(!s_BeginScene, "Scene already begun");
			s_BeginScene = true;

			shader->Bind();

			light.SetUniforms(*shader, camera);
			shader->SetMat4("u_View", camera.m_View);
			shader->SetMat4("u_Proj", camera.m_Proj);

			s_ActiveShader = shader;
		}

		template<typename Mat>
		static void Submit(DrawData<Mat>& model)
		{
			s_ActiveShader->Bind();

			model.m_Material.SetUniforms(*s_ActiveShader);
			s_ActiveShader->SetMat4("u_Model", model.m_Transform);

			model.m_Mesh.VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, model.m_Mesh.IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
		}

		static void EndScene()
		{
			JOLT_ASSERT(s_BeginScene, "Call must me preceded by Renderer::BeginScene");
			s_BeginScene = false;
			s_ActiveShader = nullptr;
		}

	private:
		static bool s_BeginScene;
		static Shader* s_ActiveShader;
	};

}