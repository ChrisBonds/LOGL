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
	static const float cubeVerticesPosNormal[]{
		//pos				  //normal
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	void configureBuffers() { //invalid draw issue has to be here right?  
		VAO cubevao;
		VAO lightCubevao;
		VBO vbo;
		EBO ebo;
		cubevao.Init("cubeVAO");
		lightCubevao.Init("lightCubeVAO");
		//vbo.Init(cubeVertices, sizeof(cubeVertices), 5 * sizeof(float), "VBO");
		vbo.Init(cubeVerticesPosNormal, sizeof(cubeVerticesPosNormal), 6 * sizeof(float), "VBO");
		ebo.Init(cubeIndices, sizeof(cubeIndices), "EBO");

		//bind ebo to vbo
		glVertexArrayVertexBuffer(cubevao.id, 0, vbo.id, 0, vbo.Stride);
		glVertexArrayElementBuffer(cubevao.id, ebo.id);

		//position location = 0
		glEnableVertexArrayAttrib(cubevao.id, 0);
		glVertexArrayAttribFormat(cubevao.id, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(cubevao.id, 0, 0);
		// 	glEnableVertexAttribArray(0); ?
		//NORMAL location = 1
		glEnableVertexArrayAttrib(cubevao.id, 1);
		glVertexArrayAttribFormat(cubevao.id, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		glVertexArrayAttribBinding(cubevao.id, 1, 0); 	

		//vertex attributes for lightcubeVAO
		glVertexArrayVertexBuffer(lightCubevao.id, 0, vbo.id, 0, vbo.Stride);
		glVertexArrayElementBuffer(lightCubevao.id, ebo.id);

		glEnableVertexArrayAttrib(lightCubevao.id, 0);
		glVertexArrayAttribFormat(lightCubevao.id, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(lightCubevao.id, 0, 0);
		glEnableVertexArrayAttrib(lightCubevao.id, 1);
		glVertexArrayAttribFormat(lightCubevao.id, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		glVertexArrayAttribBinding(lightCubevao.id, 1, 0);
	}
};