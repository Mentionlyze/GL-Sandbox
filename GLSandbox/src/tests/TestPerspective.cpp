#include "TestPerspective.h"
#include "imgui/imgui.h"

namespace test
{
	TestPerspective::TestPerspective() :
		m_Vertices{
			-0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 1.0f
		},
		m_Indices{
			0, 1, 2,
			2, 3, 0
		},
		m_VertexArray(),
		m_VertexBuffer(m_Vertices, sizeof(m_Vertices)),
		m_VertexBufferLayout(),
		m_IndexBuffer(m_Indices, 6),
		m_Shader("res/shaders/shader.vert", "res/shaders/shader.frag"),
		m_Texture("res/textures/texture.jpg"),
		m_Proj(glm::perspective(glm::radians(55.0f), 1080.0f / 720.0f, 1.0f, 100.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
		m_RotateRadians(0.0f)
	{
		m_Shader.Bind();

		m_VertexBufferLayout.Push<float>(2);
		m_VertexBufferLayout.Push<float>(2);

		m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferLayout);

		m_Shader.SetInt("u_Texture", 0);
	}

	TestPerspective::~TestPerspective() {}

	void TestPerspective::OnUpdate(float deltaTime) 
	{

	}

	void TestPerspective::OnRender() 
	{
		glClearColor(0.2, 0.3, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(m_RotateRadians), glm::vec3(1.0f, 0.0f, -3.0f));
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader.SetMat4("u_MVP", mvp);

		m_Shader.Bind();
		m_VertexArray.Bind();
		m_IndexBuffer.Bind();
		m_Texture.Bind();

		unsigned int count = m_IndexBuffer.GetCount();

		glDrawElements(GL_TRIANGLES, m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void TestPerspective::OnImGuiRender() 
	{
		ImGui::SliderFloat("radians", &m_RotateRadians, -100.0, 100.0);
	}
}