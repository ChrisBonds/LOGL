#pragma once
#include <unordered_map>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//	structs with only 1 init function are allowed to be defined in the header because i said so
//  mutables for dynamic draw and immutables for static draw or other way around?
//	TODO : buffers.cpp instead of this shit in the headers
struct VAO { //init first 
	std::string Name;
	GLuint VAOid = 0;

	void Init(std::string name) { //we dont know the data inside it 
		Name = name + "VAO"; //lol
		glCreateVertexArrays(1, &VAOid);
		//	BufferObjectManager::addVAO(&VAOid); //needs to operate on a current instance 
	}
	void bind();
	void unbind();
	void destroy();

};
struct VBO { //init second 
	std::string Name; //	?
	GLuint VBOid = 0;
	GLsizeiptr Size;
	GLsizeiptr Capacity;

	void Init(std::string name, GLsizeiptr initial_capacity = 0, GLenum usage = GL_STATIC_DRAW) {
		Name = name + "VBO";
		glCreateBuffers(1, &VBOid);
	}
	void setData(const void* data, GLsizeiptr bytes, GLenum usage = GL_STATIC_DRAW);
	void destroy()
};
struct EBO { //init third 
	std::string Name;
	GLuint EBOid = 0;

	void Init(std::string name) {
		Name = name + "EBO";
		glCreateBuffers(1, &EBOid);
	}
	void setData();
	void destroy();
};

class BufferObjectManager {
public :
		BufferObjectManager() = default; //keep defaults for now 
		~BufferObjectManager();

		//DSA 
		void addVAO(GLuint &vao)const; //reference vertex buffer information 
		void addVBO(GLuint &vbo)const; //standard buffer object 
		void addEBO(GLuint &ebo)const; //vertex index reference array 

		std::unordered_map<std::string, GLuint>& getBuffers()const; 
		GLuint getBuffer(std::string name)const;
//	this is definitely jus not quite right
private :
	std::unordered_map<std::string, GLuint*> buffers_;
};