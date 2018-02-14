#include "Camera.h"

Camera::Camera(
	glm::vec3 position, glm::vec3 up, float yaw, float pitch, float roll) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	Roll = roll;
	updateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix() {
	// position, target, up vector
	glm::mat4 viewMatrix = glm::lookAt(Position, Position + Front, Up);

	//std::cout << Position.x << ", " << Position.y << ", " << Position.z <<  std::endl;

	return viewMatrix;
}

void Camera::Rotate(float angle) {
	
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
	case ROLL_LEFT:
		//Front = glm::rotate(Front, 1.0f * velocity, glm::vec3(0.0f, 1.0f, 1.0f));
		//Position += glm::cross(Front, Up);
		Roll += 20.0f * velocity;
		Rotate(Roll);
		break;
	case ROLL_RIGHT:
		//Front = glm::rotate(Front, 1.0f * velocity * -1.0f, glm::vec3(0.0f, 1.0f, 1.0f));
		//Position -= glm::cross(Front, Up);
		Roll -= 20.0f * velocity;
		Rotate(Roll);
		break;
	case MOVEMENT_UP:
		Position += WorldUp * velocity;
		break;
	case MOVEMENT_DOWN:
		Position -= WorldUp * velocity;
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
		Zoom -= yoffset * 2.0f;
	
	if (Zoom <= 1.0f)
		Zoom = 1.0f;

	if (Zoom >= 45.0f)
		Zoom = 45.0f;

}

void Camera::IncreaseMovementSpeed(float value)
{
	MovementSpeed += value;
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

	/*Up.x = cos(glm::radians(Roll));
	Up.y = sin(glm::radians(Roll));
	Up = glm::normalize(Up);*/

}
