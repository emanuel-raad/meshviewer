#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
	cameraPos_ = cameraPos;
	cameraFront_ = cameraFront;
	cameraUp_ = cameraUp;
	worldUp_ = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight_ = glm::normalize(glm::cross(cameraFront_, worldUp_));
	
	fov_ = 45.0f;
	yaw_ = -90.0f;
	pitch_ = 0.0f;
}

Camera::~Camera()
{
}

void Camera::scrollScreen(double yOffset)
{
	if (fov_ >= 1.0f && fov_ <= 45.0f)
		fov_ -= yOffset;
	if (fov_ <= 1.0f)
		fov_ = 1.0f;
	if (fov_ >= 45.0f)
		fov_ = 45.0f;
}

void Camera::rotateScreen(double xoffset, double yoffset)
{
	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw_ += xoffset;
	pitch_ += yoffset;

	if (pitch_ > 89.0f)
		pitch_ = 89.0f;
	if (pitch_ < -89.0f)
		pitch_ = -89.0f;

	updateCameraVectors();
}

void Camera::panScreen(DIRECTION direction, float deltaTime)
{
	float velocity = 2.0f * deltaTime;
	if (direction == UP)
		cameraPos_ += cameraUp_ * velocity;
	if (direction == DOWN)
		cameraPos_ -= cameraUp_ * velocity;
	if (direction == FORWARD)
		cameraPos_ += cameraFront_ * velocity;
	if (direction == BACKWARD)
		cameraPos_ -= cameraFront_ * velocity;
	if (direction == LEFT)
		cameraPos_ -= cameraRight_ * velocity;
	if (direction == RIGHT)
		cameraPos_ += cameraRight_ * velocity;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	
	cameraFront_ = glm::normalize(front);
	cameraRight_ = glm::normalize(glm::cross(cameraFront_, worldUp_));
	cameraUp_ = glm::normalize(glm::cross(cameraRight_, cameraFront_));
}

float Camera::getFov()
{
	return fov_;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_);
}