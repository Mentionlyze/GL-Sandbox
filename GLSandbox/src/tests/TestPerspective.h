#pragma once

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

namespace test {
	class TestPerspective : public Test
	{
	private:
		float m_Vertices[20];
		unsigned int m_Indices[6];

		VertexArray m_VertexArray;
		VertexBuffer m_VertexBuffer;
		VertexBufferLayout m_VertexBufferLayout;
		IndexBuffer m_IndexBuffer;
		Shader m_Shader;
		Texture m_Texture;

		glm::mat4 m_Proj;
		glm::mat4 m_View;
		float m_RotateRadians;
		
	public:
		TestPerspective();
		~TestPerspective();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:

	};
}

