#pragma once

#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

enum CaemeraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

static const float YAW = -90.0f;
static const float PITCH = 0.0f;
static const float SPEED = 2.5f;
static const float SENSITIVITY = 0.1f;
static const float ZOOM = 45.0f;


class Camera
{
public:
	glm::vec3 c_Position;
	glm::vec3 c_Front;
	glm::vec3 c_Up;
	glm::vec3 c_Right;
	glm::vec3 c_WorldUp;

	float c_Yaw;
	float c_Pitch;

	float c_MovementSpeed;
	float c_MouseSensitivity;
	float c_Zoom;

public:
	Camera(	glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
	float yaw = YAW,
	float pitch = PITCH
);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~Camera();

	void ProcessKeyboard(CaemeraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffest);

	glm::mat4 GetViewMatrix() { return glm::lookAt(c_Position, c_Position + c_Front, c_Up); }
	float GetZoom() { return c_Zoom; }

	void UpdateCameraVecotrs();
private:
};

