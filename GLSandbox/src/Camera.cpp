#include "Camera.h"



Camera::Camera(
	glm::vec3 position,
	glm::vec3 up,
	float yaw,
	float pitch
) :
	c_Front(glm::vec3(0.0f, 0.0f, -0.1f)),
	c_MovementSpeed(SPEED),
	c_MouseSensitivity(SENSITIVITY),
	c_Zoom(ZOOM)
{
	c_Position = position;
	c_WorldUp = up;
	c_Yaw = yaw;
	c_Pitch = pitch;
	UpdateCameraVecotrs();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
	c_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
	c_MovementSpeed(SPEED),
	c_MouseSensitivity(SENSITIVITY),
	c_Zoom(ZOOM)
{
	c_Position = glm::vec3(posX, posY, posZ);
	c_WorldUp = glm::vec3(upX, upY, upZ);
	c_Yaw = yaw;
	c_Pitch = pitch;
	UpdateCameraVecotrs();
}

Camera::~Camera() {}

void Camera::UpdateCameraVecotrs()
{
	glm::vec3 front;
	front.x = cos(glm::radians(c_Yaw)) * cos(glm::radians(c_Pitch));
	front.y = sin(glm::radians(c_Pitch));
	front.z = sin(glm::radians(c_Yaw)) * cos(glm::radians(c_Pitch));

	c_Front = glm::normalize(front);

	c_Right = glm::normalize(glm::cross(c_Front, c_WorldUp));
	c_Up = glm::normalize(glm::cross(c_Right, c_Front));
}

void Camera::ProcessKeyboard(CaemeraMovement direction, float deltaTime)
{
	float velocity = c_MovementSpeed * deltaTime;
	if (direction == FORWARD)
		c_Position += c_Front * velocity;
	if (direction == BACKWARD)
		c_Position -= c_Front * velocity;
	if (direction == LEFT)
		c_Position -= c_Right * velocity;
	if (direction == RIGHT)
		c_Position += c_Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= c_MouseSensitivity;
	yoffset *= c_MouseSensitivity;

	c_Yaw += xoffset;
	c_Pitch += yoffset;

	if (constrainPitch)
	{
		if (c_Pitch > 89.0f)
			c_Pitch = 89.0f;
		if (c_Pitch < -89.0f)
			c_Pitch = -89.0f;
	}

	UpdateCameraVecotrs();
}

void Camera::ProcessMouseScroll(float yoffest)
{
	c_Zoom -= (float)yoffest;
	if (c_Zoom < 1.0f)
		c_Zoom = 1.0f;
}
