#include "TestCamera.h"

#include "imgui/imgui.h"

namespace test
{
	TestCamera::TestCamera() :
        m_Camera(glm::vec3(0.0f, 0.0f, 3.0f)),
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
        m_Texture("res/textures/container.jpg"),
        m_DeltaTime(0.0f),
        m_FirstMouse(true),
        lastX(1080.0f / 2.0),
        lastY(720.0f / 2.0)
    {
        glEnable(GL_DEPTH_TEST);

        m_Shader.Bind();

        m_VertexBufferLayout.Push<float>(3);
        m_VertexBufferLayout.Push<float>(2);

        m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferLayout);

        m_Shader.SetInt("u_Texture", 0);

        m_View = m_Camera.GetViewMatrix();
        m_Proj = glm::perspective(glm::radians(m_Camera.GetZoom()), 1080.0f / 720.0f, 1.0f, 100.0f);
	}

    TestCamera::~TestCamera() 
    {
        glDisable(GL_DEPTH_TEST);
    }

    void TestCamera::OnUpdate(float deltaTime) {}

    void TestCamera::OnRender()
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        m_Camera.UpdateCameraVecotrs();

        m_Shader.Bind();

        m_View = m_Camera.GetViewMatrix();
        m_Proj = glm::perspective(glm::radians(m_Camera.GetZoom()), 1080.0f / 720.0f, 1.0f, 100.0f);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(1.0, 0.3f, 0.05f));

        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader.SetMat4("u_MVP", mvp);

        m_VertexArray.Bind();
        m_Texture.Bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void TestCamera::OnImGuiRender()
    {
        ImGui::SliderFloat("Camera Zoom", &m_Camera.c_Zoom, 1.0f, 100.0f);
        ImGui::SliderFloat3("Camera Position", &m_Camera.c_Position.x, -100.0f, 100.0f);
        ImGui::SliderFloat("Camera Pitch", &m_Camera.c_Pitch, -89.0f, 89.0f);
        ImGui::SliderFloat("Camera Yaw", &m_Camera.c_Yaw, -180.0f, 0.0f);
    }
}
