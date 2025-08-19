//#define GLFW_STATIC
//#include "GL_Compatability/GL_chris.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "WindowManager.hpp"
//#include "ShaderManager.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.hpp"
//	if you are reading this welcome to the mess
#include "API.hpp"


int main() {

	//init backend w/ glfw, glad and window
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize GLAD" << std::endl;
		return -2;
	}

	//config openGL state
	glEnable(GL_DEPTH_TEST);

	//init shaders
	Shaders::initShaders();
	/*auto& shaderManagerRef = ShaderManager::instance();
	shaderManagerRef.loadProgram("OpenGL_triangle", R"(C:\Users\cwbon\Shaders\FRESH\res\shaders\OpenGL\test.vert)", R"(C:\Users\cwbon\Shaders\FRESH\res\shaders\OpenGL\test.frag)");
	*/
	// would like a global array of shader programs cuz imma start using differnt shader programs now
	//Shader shader(R"(C:\Users\cwbon\Shaders\FRESH\res\shaders\OpenGL\test.vert)", R"(C:\Users\cwbon\Shaders\FRESH\res\shaders\OpenGL\test.frag)");

	glm::vec3 cubePositions[] = { //belongs in Renderer
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	//	too afraid to lose this 
	//	//init textures here, could do all the manipulation in a seperate space and just call them for use here cuz main should really just be calling everything associated with the renderloop 
	//	//std::unordered_map<std::filesystem::path, GLuint*> textureCache;
	//	//	TextureInfo containerTextureInfo(std::filesystem::path(R"(C:\Users\cwbon\Shaders\FRESH\res\textures// \container.jpg)"), GL_TEXTURE0);
	//	//	Texture containerTexture(containerTextureInfo);
	//	//	TextureInfo epicTextureInfo(std::filesystem::path(R"(C:\Users\cwbon\Shaders\FRESH\res\textures//  \awesomeface.png)"), GL_TEXTURE1, GL_RGBA);
	//	//	Texture epicTexture(epicTextureInfo);
	//	//	TextureInfo joshTextureInfo(std::filesystem::path(R"(C:\Users\cwbon\Shaders\FRESH\res\textures/   \josh.png)"), /GL_TEXTURE2, GL_RGBA);
	//	//	Texture joshTexture(joshTextureInfo);
	//	//	
	//	/*shader.use();
	//	shader.setInt("texture1", 0);
	//	shader.setInt("texture2", 1);
	//	shader.setInt("texture3", 2);*/
	//
	//	//matrix outside render loop for const
	//	//glm::mat4 trans = glm::mat4(1.0f);
	//	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); //mat4 /takes /f vec3 doesnt need f? what is this, also w auto set to 1 
	//	//trans = glm::scale(trans, glm::vec3(0.5, .5, .5));
	//
	//	//it appears that we may need to make a transform class
	//	//unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
	//	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	//	//	int modelLoc = glGetUniformLocation(shader.ID, "model");
	//	//	int viewLoc = glGetUniformLocation(shader.ID, "view");
	//	//	int projectionLoc = glGetUniformLocation(shader.ID, "projection");
	//
	//	//create these in the render loop
	////		//coordinate systems
	////		glm::mat4 model = glm::mat4(1.0f);
	////		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	////		glm::mat4 view = glm::mat4(1.0f);
	////		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	////		glm::mat4 projection;
	////		projection = glm::perspective(glm::radians(42.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	//too afraid to lose this

		// Renderer::startRenderLoop()

	Camera camera(glm::vec3(0.0f, 0.0f, -3.0f));
	float dt = 0.0;
	float lastFrame = 0.0;
	float currentFrame;
	//render loop
	while (!glfwWindowShouldClose(window)) {
		currentFrame = static_cast<float>(glfwGetTime());
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window, camera, dt);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//	Renderer::iterate all the things i want to render
		//	Textures::activateTextures for this thing i am trying to render
		/*glActiveTexture(containerTexture.getInfo().unit);
		glBindTexture(containerTexture.getInfo().textureDimension, containerTexture.getID());
		glActiveTexture(epicTexture.getInfo().unit);
		glBindTexture(epicTexture.getInfo().textureDimension, epicTexture.getID());
		glActiveTexture(joshTexture.getInfo().unit);
		glBindTexture(joshTexture.getInfo().textureDimension, joshTexture.getID());*/
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::mat4(1.0f);

		projection = glm::perspective(glm::radians(camera.zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

		unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
		unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection");    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		//manipulating color with time 

		//hi
		////float timeValue = glfwGetTime(); //value gets updated after program is in use
		////float greenValue = (sin(timeValue) / 2.0f) + .5f;
		////int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");
		////glUniform4f(vertexColorLocation, .0f, greenValue, .0f, 1.0f);
		////glm::mat4 trans = glm::mat4(1.0f);
		////trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		////trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		////glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		//hi

		//draw a bunch of the same instance

		//glBindVertexArray(VAO);//no idea why we call after using the program
		////glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//for (int i = 0; i < 10; i++) {
		//	glm::mat4 model = glm::mat4(1.0f);
		//	model = glm::translate(model, cubePositions[i]);
		//	float angle = 20.0f * i;
		//	model = glm::rotate(model, glm::radians(angle) * (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
		//	shader.setMat4("model", model);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glfwSwapBuffers(window); //double buffer	
		glfwPollEvents();
	}
	//	Renderer::cleanupBackend or some shit more diverse than just cleanupBuffers
	API::DestroyEverything();
}