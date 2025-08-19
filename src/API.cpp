//being stupid here
#include "API.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Buffers.hpp"
#include <iostream>

namespace API { //wrap everything into this
	void DestroyEverything() {
		glDeleteVertexArrays(1, &Buffers::g_buffers.at("VAO"));
		glDeleteBuffers(1, &Buffers::g_buffers.at("VBO"));
		glDeleteBuffers(1, &Buffers::g_buffers.at("EBO"));
		
		glfwTerminate();
	}
}