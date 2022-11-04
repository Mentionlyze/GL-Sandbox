#pragma once

#include "Test.h"

#include "Camera.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "GLFW/glfw3.h"


namespace test
{
	class TestCamera : public Test
	{
	public:
		Camera m_Camera;

		float m_Vertices[180];

		VertexArray m_VertexArray;
		VertexBuffer m_VertexBuffer;
		VertexBufferLayout m_VertexBufferLayout;
		Shader m_Shader;
		Texture m_Texture;

		float m_DeltaTime;
		bool m_FirstMouse;

		float lastX;
		float lastY;

		glm::mat4 m_Proj;
		glm::mat4 m_View;

		TestCamera();
		~TestCamera();

		void SetEventCallback(GLFWwindow* window);

		void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		void processInput(GLFWwindow* window);


		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}

