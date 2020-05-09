#pragma once
#include "Camera/Camera.h"
#include "OpenGL/Shader.h"

#include "DrawData.h"
#include "MaterialDefs/MatDummy.h"
#include "LightDefs/LightDummy.h"

#include <glad/glad.h>

namespace Jolt
{
	template<typename Light, typename Mat>
	class Renderer
	{
	public:
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

		static void Submit(DrawData<Mat>& model)
		{
			model.m_Mesh.m_VertexArray.Bind();
			s_ActiveShader->Bind();
			s_ActiveShader->SetMat4("u_Model", model.m_Transform);

			for (auto& material_mapper : model.m_Materials)
			{
				material_mapper.GetMaterial()->SetUniforms(*s_ActiveShader);

				glDrawElements(GL_TRIANGLES, material_mapper.End() - material_mapper.Begin(), GL_UNSIGNED_INT, (const GLvoid*)(material_mapper.Begin() * sizeof(GLuint)));
			}
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

	template<typename Light, typename Mat>
	bool Renderer<Light, Mat>::s_BeginScene = false;
	template<typename Light, typename Mat>
	Shader* Renderer<Light, Mat>::s_ActiveShader = nullptr;

	// Class template specialisation for Renderer that takes no material or lights
	template<> class Renderer<LightDummy, MatDummy>
	{
	public:
		static void BeginScene(Shader* shader, Camera camera)
		{
			JOLT_ASSERT(!s_BeginScene, "Scene already begun");
			s_BeginScene = true;

			shader->Bind();

			shader->SetMat4("u_View", camera.m_View);
			shader->SetMat4("u_Proj", camera.m_Proj);

			s_ActiveShader = shader;
		}

		static void Submit(DrawData<MatDummy>& model)
		{
			s_ActiveShader->Bind();

			s_ActiveShader->SetMat4("u_Model", model.m_Transform);

			model.m_Mesh.m_VertexArray.Bind();
			glDrawElements(GL_TRIANGLES, model.m_Mesh.m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
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