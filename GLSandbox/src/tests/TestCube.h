#pragma once

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

namespace test
{
	class TestCube : public Test
	{
	private:
		float m_Vertices[180];

		VertexArray m_VertexArray;
		VertexBuffer m_VertexBuffer;
		VertexBufferLayout m_VertexBufferLayout;
		Shader m_Shader;
		Texture m_Texture;

		glm::mat4 m_Proj;
		glm::mat4 m_View;

		float m_RotateAngel;
	public:
		TestCube();
		~TestCube();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:

	};

}
