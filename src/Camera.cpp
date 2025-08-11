#include "Camera.hpp"

	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //no window context available rn 
// i fucking hate these variable names

Camera::Camera(glm::vec3 Position,
			   glm::vec3 Up,
			   float Yaw,
			   float Pitch) 
	: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY),	zoom(ZOOM)
{
	pos = Position;
	worldUp = Up;
	yaw = Yaw;
	pitch = Pitch;
	Camera::updateCameraVectors();
	CAMERAS.push_back(this);
}
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float Yaw, float Pitch)
	: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
	pos = glm::vec3(posX, posY, posZ);
	worldUp = glm::vec3(upX, upY, upZ);
	yaw = Yaw;
	pitch = Pitch;
	Camera::updateCameraVectors();
	CAMERAS.push_back(this);
}
//using euler 
void Camera::updateCameraVectors() {
	glm::vec3 front = glm::normalize(glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
											   sin(glm::radians(pitch)),
											   sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
	//std::cout << "front : (" << front.x <<" , " << front.y << " , "<< front.z << ")\n\n";
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(pos, pos + front, up);
}
void Camera::processKeyboard(CameraMovement dir, float dt) {
	float v = movementSpeed * dt;
	if(dir == FORWARD) {
		pos += front * v;
	}
	else if (dir == BACKWARD) {
		pos -= front * v;
	}
	else if (dir == LEFT) {
		pos -= right * v;
	}
	else if (dir == RIGHT) {
		pos += right * v;
	}
}
void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrain_pitch) {
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;
	yaw += xoffset;
	pitch += yoffset;

	if (constrain_pitch) {
		if (pitch > 89.9f) {
			pitch = 89.9f;
		}
		if (pitch < -89.9f) {
			pitch = -89.9f;
		}
	}
	Camera::updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
	zoom -= yoffset;
	if (zoom < 1.0) {
		zoom = 1.0;
	}if (zoom > 45.0) {
		zoom = 45.0;
	}
}
Camera& Camera::getCurrentCamera() {
	static Camera defaultCam;
	if (CAMERAS.empty()) {
		std::cout << "no cameras found, returning default" << std::endl;
		return defaultCam;
	}
	//could have different cameras for different debug views
	return *CAMERAS.front(); //only one camera for now
}
Camera::~Camera() {
	//need a proper destructor (for list of cameras) 
	auto it = std::find(CAMERAS.begin(), CAMERAS.end(), this);
	if (it != CAMERAS.end()) {
		CAMERAS.erase(it);
	}
}

//have to define static memeber outside of class definition idk man 
std::vector<Camera*> Camera::CAMERAS;