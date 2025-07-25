//#define GLFW_STATIC
//#include "GL_Compatability/GL_chris.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "WindowManager.hpp"
//#include "ShaderResourceManager.hpp"
#include "Shader.hpp"

static int WINDOW_WIDTH = 800;
static int WINDOW_HEIGHT = 600;


int main() {

	//initialize glfw and window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "hello huzz", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //weird that this is legal


	//load glad opengl function pointers 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //have to cast glfw process to glad process i wonder how that works
		std::cout << "failed to initialize GLAD" << std::endl;
		return -2;
	}

	//compile shaders here 

	/*auto& shaderManagerRef = ShaderResourceManager::instance();
	shaderManagerRef.loadProgram("OpenGL_triangle", R"(C:\Users\cwbon\Shaders\FRESH\res\shaders\OpenGL\test.vert)", R"(C:\Users\cwbon\Shaders\FRESH\res\shaders\OpenGL\test.frag)");
	*/ 
	Shader shader(R"(C:\Users\cwbon\Shaders\FRESH\res\shaders\OpenGL\test.vert)", R"(C:\Users\cwbon\Shaders\FRESH\res\shaders\OpenGL\test.frag)");

	float vertices[] = {
		//positions			 //colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	//so much shit here
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * (sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//sepcify offset
	glEnableVertexAttribArray(1);
	

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); //often unnecessary to unbind VAO for some reason i dont understand idk prolly gonna need to refer back to this section often
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glUseProgram(shaderManagerRef.getProgram("OpenGL_triangle").id); //evil syntax
		shader.use();
		float timeValue = glfwGetTime(); //value gets updated after program is in use
		float greenValue = (sin(timeValue) / 2.0f) + .5f;
		int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");

		glUniform4f(vertexColorLocation, .0f, greenValue, .0f, 1.0f);
		glBindVertexArray(VAO);//no idea why we call after using the program
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window); //double buffer	
		glfwPollEvents();
	}


	//clean glfw resources
	glfwTerminate();
	return 0;
}