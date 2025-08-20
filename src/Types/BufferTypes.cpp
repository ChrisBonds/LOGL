#include "Types/BufferTypes.hpp"
#include "Buffers.hpp"

void VAO::Init(std::string name) {
	//we dont know the data inside it 
	Name = name; //lol
	glCreateVertexArrays(1, &id);
	Buffers::g_buffers[Name] = id;
	//pretty sure this is all i need if im using DSA
}
void VAO::bind() {
	glBindVertexArray(id); //IDK MAN 
}
void VBO::Init(const void* data, GLsizeiptr size, unsigned int stride, std::string name, GLenum usage) {
	Name = name;
	Size = size; //not correct
	Stride = stride;
	glCreateBuffers(1, &id); //2nd param is location of names to be stored so could use g_buffers
	glNamedBufferStorage(id, Size, data, GL_DYNAMIC_STORAGE_BIT); //dynamic storage bit indicates buffer data can be changed but not size
	//might need to use glBufferStorage
	glBindBuffer(GL_ARRAY_BUFFER, id);
	//i think i just need the pointer to the id not the type or anything else like that
	Buffers::g_buffers[Name] = id;
}
void EBO::Init(const void* data, GLsizeiptr size, std::string name) {
	Name = name;
	Size = size;
	glCreateBuffers(1, &id);
	glNamedBufferStorage(id, size, data, GL_DYNAMIC_STORAGE_BIT);
	Buffers::g_buffers[Name] = id;
}

