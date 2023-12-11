#include "Camera.h"


Camera::Camera(glm::vec3 _position , glm::vec3 _up , float _yaw , float _pitch):
	forward(glm::vec3(0.0f,0.0f,-1.0f)),
	movementSpeed(SPEED),
	mouseSensitivity(SENSITIVITY),
	zoom(ZOOM),
	position(_position),
	pitch(_pitch),
	yaw(_yaw),
	worldUp(_up)
{
	UpdateCameraVector();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + forward, worldUp);

}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += forward * velocity;
	else if (direction == BACKWARD)
		position -= forward * velocity;

	if (direction == LEFT)
		position += right * velocity;
	else if (direction == RIGHT)
		position -= right * velocity;

	if (direction == LIFT)
		position += up * velocity;
	else if (direction == DOWN)
		position -= up * velocity;

}


void Camera::ProcessMouseScroll(float yoffset)
{
	zoom -= static_cast<float>(yoffset);
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}


void Camera::ProcessMouseMovement(float xoffset,float yoffset,GLboolean constrainPitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	UpdateCameraVector();
}

void Camera::UpdateCameraVector()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(front);

	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));
}
