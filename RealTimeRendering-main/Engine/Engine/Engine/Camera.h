#pragma once
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>
#include<vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	LIFT,
	DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 10.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
public:
	//camera Attributes
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;
	// ruler Angles
	float pitch;
	float yaw;
	// camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),float _yaw = YAW,float _pitch = PITCH);
	

	glm::mat4 GetViewMatrix();
	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	void ProcessMouseMovement(float xoffset,float yoffset,GLboolean constrainPitch = true);

	void ProcessMouseScroll(float yoffset);

private:
	void UpdateCameraVector();


};

