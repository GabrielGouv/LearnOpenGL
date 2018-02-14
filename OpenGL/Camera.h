#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <vector>
#include <iostream>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ROLL = 0.0f;
const float SPEED = 4.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{

public:

	static const int MOVEMENT_FORWARD = 1;
	static const int MOVEMENT_BACKWARD = 2;
	static const int MOVEMENT_LEFT = 3;
	static const int MOVEMENT_RIGHT = 4;
	static const int ROLL_LEFT = 5;
	static const int ROLL_RIGHT = 6;
	static const int MOVEMENT_UP = 7;
	static const int MOVEMENT_DOWN = 8;

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;
	float Roll;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	bool firstInit = true;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = YAW,
		float pitch = PITCH,
		float roll = ROLL);

	~Camera();

	glm::mat4 GetViewMatrix();

	void Rotate(float angle);

	void ProcessKeyBoard(int direction, float deltaTime);

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	void ProcessMouseScroll(float yoffset);

	void IncreaseMovementSpeed(float value);

private:

	void updateCameraVectors();

};

