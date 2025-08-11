#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera.hpp"
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

void processInput(GLFWwindow* window, Camera& camera, float dt);
void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void mouse_callback(GLFWwindow* window, double xpos, double ypos); //dont know how to get cameras in here 
void scroll_callback(GLFWwindow* window, double xoffset, double yofset);

