#include "WindowManager.hpp"
#include "Camera.hpp"

//does not to be its own class just yet
int WINDOW_WIDTH = 1920 * 1.5;
int WINDOW_HEIGHT = 1080 * 1.5;
float lastX = 400;
float lastY = 300;
float firstMouse = true;

void processInput(GLFWwindow* window, Camera& camera, float dt) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, dt);
    if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
        camera.processKeyboard(UP, dt);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.processKeyboard(DOWN, dt);

}

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    //mouse movement is not smooth enough 
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    //happens in processMouseMovement
    //  const float sensitivity = 0.1f;
    //  
    //  xoffset *= sensitivity;
    //  yoffset *= sensitivity;
    //  std::cout << "mouse callback xoffset : " << xoffset << "\n";
    //  std::cout << "mouse callback yoffset : " << yoffset << "\n\n\n"; 
    //  std::cout << "current camera pitch : " << Camera::getCurrentCamera().pitch << "\n";
    //  std::cout << "current camera yaw : " << Camera::getCurrentCamera().yaw << "\n\n";
    Camera::getCurrentCamera().processMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    Camera::getCurrentCamera().processMouseScroll(static_cast<float>(yoffset));
}