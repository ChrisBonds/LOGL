#pragma once
#include <unordered_map>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct VAO { //init first 
	GLuint VAOid;

	void Init() { //we dont know the data inside it 
		glGenVertexArrays(1, &VAOid);
		//
	}
};
struct VBO { //init second 
	GLuint VBOid;
	GLsizeiptr size;
	GLsizeiptr capacity;

	void Init() {

	}
};
struct EBO { //init third 
	GLuint EBOid;

	void Init() {

	}
};

class BufferObjectManager {
public :
		BufferObjectManager(); //keep defaults for now 
		~BufferObjectManager();

		void addVAO()const;
		std::unordered_map<std::string, GLuint>& getBuffers()const; 

private :
	std::unordered_map<std::string, GLuint> Buffers;
};