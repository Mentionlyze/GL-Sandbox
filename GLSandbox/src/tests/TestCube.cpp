#include "TestCube.h"
#include "imgui/imgui.h"

namespace test
{
    TestCube::TestCube() :
        m_Vertices{
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
             0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

             0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
             0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
             0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
             0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
             0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f,  0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    },


        m_VertexArray(),
        m_VertexBuffer(m_Vertices, sizeof(m_Vertices)),
        m_VertexBufferLayout(),
        m_Shader("res/shaders/cube.vert", "res/shaders/cube.frag"),
        m_Texture("res/textures/container.jpg")
	{
        glEnable(GL_DEPTH_TEST);

        m_Shader.Bind();

        m_VertexBufferLayout.Push<float>(3);
        m_VertexBufferLayout.Push<float>(2);

        m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferLayout);

        m_Shader.SetInt("u_Texture", 0);

        m_Proj = glm::perspective(glm::radians(75.0f), 1080.0f / 720.0f, 1.0f, 100.0f);
        m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

        m_RotateAngel = 30.0f;
	}

	TestCube::~TestCube()
	{
        glDisable(GL_DEPTH_TEST);
	}
    
    void TestCube::OnUpdate(float deltaTime)
    {

    }

    void TestCube::OnRender()
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2, 0.3, 0.5, 1.0);

        m_Shader.Bind();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(glm::mat4(1.0f), glm::radians(m_RotateAngel), glm::vec3(1.0, 0.3f, 0.05f));

        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader.SetMat4("u_MVP", mvp);

        m_VertexArray.Bind();
        m_Texture.Bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void TestCube::OnImGuiRender()
    {
        ImGui::SliderFloat("Rotate Angle", &m_RotateAngel, -360.f, 360.0f);
    }
}