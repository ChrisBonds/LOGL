#include "Buffers.hpp"
#include <glad/glad.h>

namespace Buffers {
	std::unordered_map<std::string, GLuint> g_buffers;
	static const float cubeVertices[] = { //position and texcoord
		// positions         // texcoords
		-0.5f,-0.5f,-0.5f,   0.0f,0.0f,
		 0.5f,-0.5f,-0.5f,   1.0f,0.0f,
		 0.5f, 0.5f,-0.5f,   1.0f,1.0f,
		-0.5f, 0.5f,-0.5f,   0.0f,1.0f,
		-0.5f,-0.5f, 0.5f,   0.0f,0.0f,
		 0.5f,-0.5f, 0.5f,   1.0f,0.0f,
		 0.5f, 0.5f, 0.5f,   1.0f,1.0f,
		-0.5f, 0.5f, 0.5f,   0.0f,1.0f
	};
	static const unsigned int cubeIndices[] = {
		0,1,2, 2,3,0, // back
		4,5,6, 6,7,4, // front
		4,5,1, 1,0,4, // bottom
		7,6,2, 2,3,7, // top
		4,0,3, 3,7,4, // left
		5,1,2, 2,6,5  // right
	};
	void configureBuffers() { //invalid draw issue has to be here right?  
		VAO vao;
		VBO vbo;
		EBO ebo;
		vao.Init("VAO");
		vbo.Init(cubeVertices, sizeof(cubeVertices), 5 * sizeof(float), "VBO");
		ebo.Init(cubeIndices, sizeof(cubeIndices), "EBO");

		//bind ebo to vbo
		glVertexArrayVertexBuffer(vao.id, 0, vbo.id, 0, vbo.Stride);
		glVertexArrayElementBuffer(vao.id, ebo.id);

		//position location = 0
		glEnableVertexArrayAttrib(vao.id, 0);
		glVertexArrayAttribFormat(vao.id, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao.id, 0, 0);
		// 	glEnableVertexAttribArray(0); ?
		//texcoord location = 1
		glEnableVertexArrayAttrib(vao.id, 1);
		glVertexArrayAttribFormat(vao.id, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		glVertexArrayAttribBinding(vao.id, 1, 0); 	
	}
};