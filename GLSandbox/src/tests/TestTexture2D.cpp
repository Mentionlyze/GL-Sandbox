#include "TestTexture2D.h"
#include "imgui/imgui.h"

namespace test
{
	TestTexture2D::TestTexture2D() : m_Translate(glm::vec3(200, 200, 0))
	{
		float vertices[] = {
			100.0f, 100.0f, 0.0f, 0.0f,
			300.0f, 100.0f, 1.0f, 0.0f,
			300.0f, 300.0f, 1.0f, 1.0f,
			100.0f, 300.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/shader.vert", "res/shaders/shader.frag");
		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>("res/textures/texture.jpg");
		m_Shader->SetInt("u_Texture", 0);

		m_Proj = glm::ortho(0.0, 1080.0, 0.0, 720.0, -1.0, 1.0);
		m_View = glm::scale(glm::mat4(1.0), glm::vec3(0.5, 0.5, 1.0));
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender() 
	{
		glClearColor(0.2, 0.3, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translate);

		glm::mat4 mvp = m_Proj * m_View * model;

		m_Shader->Bind();
		m_Shader->SetMat4("u_MVP", mvp);

		m_VertexArray->Bind();
		m_IndexBuffer->Bind();
		m_Texture->Bind();

		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat2("Translate", &m_Translate.x, 0.0, 1080.0);
	}
}