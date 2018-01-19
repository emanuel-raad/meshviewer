#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	enum Direction {
		UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD
	};

	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
	~Camera();

	void scrollScreen(double yOffset);
	void rotateScreen(double xoffset, double yoffset);
	void panScreen(double xpos, double ypos);
	void updateCameraVectors();
	float getFov();
	glm::mat4 getViewMatrix();

private:
	glm::vec3 cameraPos_;
	glm::vec3 cameraFront_;
	glm::vec3 cameraUp_;
	glm::vec3 cameraRight_;
	glm::vec3 worldUp_;

	float fov_;
	float yaw_;
	float pitch_;
};