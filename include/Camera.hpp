#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <vector>
#include <iostream>

//stupid LOGL uses euler angles so imma (maybe) have to rewrite with quarternions

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values, should maybe be in globals 
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 42.0f;

class Camera {
public:
	static std::vector<Camera*> CAMERAS;
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	Camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f),
		float Yaw = YAW,
		float Pitch = PITCH);
	// construct w/ floats
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~Camera();
	glm::mat4 getViewMatrix();
	void processKeyboard(CameraMovement dir, float dt);
	void processMouseMovement(float xoffset, float yoffset, GLboolean constrain_pitch = true);
	void processMouseScroll(float yoffset);
	static Camera& getCurrentCamera();

private : 
	void updateCameraVectors();
};

#endif // !CAMERA_HPP