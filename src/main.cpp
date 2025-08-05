//#define GLFW_STATIC
//#include "GL_Compatability/GL_chris.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "WindowManager.hpp"
//#include "ShaderResourceManager.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	//buffer class fo shizzle 
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*(sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3 * sizeof(float)));//sepcify offset
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0); //often unnecessary to unbind VAO for some reason i dont understand idk prolly gonna need to refer back to this section often
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//init textures here 
	std::unordered_map<std::filesystem::path, GLuint> textureCache;

	TextureInfo containerTextureInfo(std::filesystem::path(R"(C:\Users\cwbon\Shaders\FRESH\res\textures\container.jpg)"), GL_TEXTURE0);
	//TextureInfo(R"(C:\Users\cwbon\Shaders\FRESH\res\textures\container.jpg)");
	Texture containerTexture(containerTextureInfo);
	//Texture epicTexture(R"(C:\Users\cwbon\Shaders\FRESH\res\textures\awesomeface.png)");
	TextureInfo epicTextureInfo(std::filesystem::path(R"(C:\Users\cwbon\Shaders\FRESH\res\textures\awesomeface.png)"), GL_TEXTURE1, GL_RGBA);
	Texture epicTexture(epicTextureInfo);

	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	//matrix outside render loop for const
	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); //mat4 /takes /f vec3 doesnt need f? what is this, also w auto set to 1 
	//trans = glm::scale(trans, glm::vec3(0.5, .5, .5));

	//it appears that we may need to make a transform class
	unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	//render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO : bindings in class

		glActiveTexture(containerTexture.getInfo().unit);
		glBindTexture(containerTexture.getInfo().textureDimension, containerTexture.getID());
		glActiveTexture(epicTexture.getInfo().unit);
		glBindTexture(epicTexture.getInfo().textureDimension, epicTexture.getID());


		//glUseProgram(shaderManagerRef.getProgram("OpenGL_triangle").id); //evil syntax
		shader.use();
		//float timeValue = glfwGetTime(); //value gets updated after program is in use
		//float greenValue = (sin(timeValue) / 2.0f) + .5f;
		//int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");
		//glUniform4f(vertexColorLocation, .0f, greenValue, .0f, 1.0f);
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


		glBindVertexArray(VAO);//no idea why we call after using the program
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window); //double buffer	
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//clean glfw resources
	glfwTerminate();
	return 0;
}