//being stupid here
#include "API.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Buffers.hpp"
#include <iostream>

namespace API { //wrap everything into this
	void destroyEverything() {
        std::unordered_map<std::string, GLuint> buffers = Buffers::getBuffers();
		std::cout << buffers.at("VAO") << std::endl;
		glDeleteVertexArrays(1, &buffers.at("VAO"));
		glDeleteBuffers(1, & buffers.at("VBO"));
		glDeleteBuffers(1, & buffers.at("EBO"));
		
		glfwTerminate();
	}
}