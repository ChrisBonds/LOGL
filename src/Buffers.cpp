#include "Buffers.hpp"
#include "Models.hpp"
namespace Buffers {
	void configureBuffers() {
		//and then do work thats gonna change a lot here? and write a bunch of helpers?  
		VAO vao;
		VBO vbo;
		EBO ebo;
		vao.Init();
		vbo.Init(Models::g_cubeVerticies);
		ebo.Init(Models::g_cubeIndices);
		//
	}
};