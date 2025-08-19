#include "Buffers.hpp"
#include "Models.hpp"
#include <glad/glad.h>
namespace Buffers {
	void configureBuffers() {
		//and then do work thats gonna change a lot here? and write a bunch of helpers?  
		VAO vao;
		VBO vbo;
		EBO ebo;
		vao.Init();
		vbo.Init(Models::g_cubeVerticies, 5);
		ebo.Init(Models::g_cubeIndices);
		//bind ebo to vbo
		glVertexArrayVertexBuffer(vao.id, vao.BindingPoint++, vbo.id, 0, vbo.Stride);
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

		glBindVertexArray(vao.id);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
// Fix for E0304: Use std::pair or initializer_list for unordered_map::insert
// Also make addBuffers static as per VCR003

	static void addBuffers(std::string name, GLuint id) {
		//g_buffers.insert({name, id});
		g_buffers.emplace(name, id);
	}
	std::unordered_map<std::string, GLuint> getBuffers(){
		return g_buffers; //COPY	
	}
};