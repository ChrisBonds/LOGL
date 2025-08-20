//being stupid here
#include "API.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Buffers.hpp"
#include <iostream>

namespace API { //wrap everything into this
	void DestroyEverything() {
		glDeleteVertexArrays(1, &Buffers::g_buffers["VAO"]);
		glDeleteBuffers(1, &Buffers::g_buffers["VBO"]);
		glDeleteBuffers(1, &Buffers::g_buffers["EBO"]);
		
		glfwTerminate();
	}
}