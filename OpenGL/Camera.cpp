#include "Camera.h"

Camera::Camera(
	glm::vec3 position,
	glm::vec3 up,
	float yaw,
	float pitch) 
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
	MovementSpeed(SPEED),
	MouseSensitivity(SENSITIVITY)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyBoard(int direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;

	switch (direction) {
	case MOVEMENT_FORWARD:
		Position += Front * velocity;
		break;
	case MOVEMENT_BACKWARD:
		Position -= Front * velocity;
		break;
	case MOVEMENT_LEFT:
		Position -= Right * velocity;
		break;
	case MOVEMENT_RIGHT:
		Position += Right * velocity;
		break;
	}

	//Position.y = 0.0f;

}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch) {
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	
	if (Zoom <= 1.0f)
		Zoom = 1.0f;

	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}
