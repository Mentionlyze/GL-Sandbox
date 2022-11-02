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
		m_Texture("res/textures/texture.jpg")
	{
		m_Shader.Bind();

		m_VertexBufferLayout.Push<float>(2);
		m_VertexBufferLayout.Push<float>(2);

		m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferLayout);

		m_Shader.SetInt("u_Texture", 0);

		m_Proj = glm::perspective(glm::radians(45.0f), 1080.0f / 720.0f, 1.0f, 100.0f);
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		m_RotateRadians = 0.0f;
	}

	TestPerspective::~TestPerspective() {}

	void TestPerspective::OnUpdate(float deltaTime) 
	{

	}

	void TestPerspective::OnRender() 
	{
		glClearColor(0.2, 0.3, 0.5, 1.0);
		
		m_Shader.Bind();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(m_RotateRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)1080.0/ (float)720.0, 1.0f, 100.f);

		glm::mat4 mvp = proj * view * model;

		m_Shader.SetMat4("u_MVP", mvp);

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