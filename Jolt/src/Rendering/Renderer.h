#pragma once
#include "Camera/Camera.h"
#include "OpenGL/Shader.h"

#include "Model.h"

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

			s_Shader = shader;
		}

		template<typename Mat>
		static void Submit(Model<Mat>& model)
		{
			s_Shader->Bind();

			model.m_Material.SetUniforms(*s_Shader);
			s_Shader->SetMat4("u_Model", model.m_Transform);

			model.m_Mesh.VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, model.m_Mesh.IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
		}

		static void EndScene()
		{
			JOLT_ASSERT(s_BeginScene, "Call must me preceded by Renderer::BeginScene");
			s_BeginScene = false;
			s_Shader = nullptr;
		}

	private:
		static bool s_BeginScene;
		static Shader* s_Shader;
	};

}