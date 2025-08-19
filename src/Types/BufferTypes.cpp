#include "Types/BufferTypes.hpp"
#include "Buffers.hpp"

void VAO::Init(std::string name) {
	//we dont know the data inside it 
	Name = name + "VAO"; //lol
	glCreateVertexArrays(1, &id);
	Buffers::addBuffer(id);
	//pretty sure this is all i need if im using DSA
}
void VBO::Init(const void* data, unsigned int stride, GLenum usage, std::string name) {
	Name = name + "VBO";
	Size = sizeof(data); //not correct
	Stride = stride;
	glCreateBuffers(1, &id); //2nd param is location of names to be stored so could use g_buffers
	glNamedBufferStorage(id, Size, data, GL_DYNAMIC_STORAGE_BIT); //dynamic storage bit indicates buffer data can be changed but not size
	//might need to use glBufferStorage
	glBindBuffer(GL_ARRAY_BUFFER, id);
	//i think i just need the pointer to the id not the type or anything else like that
	Buffers::addBuffer(id);
}
void EBO::Init(const void* data, std::string name) {
	Name = name + "EBO";
	glCreateBuffers(1, &id);
	glNamedBufferStorage(id, sizeof(data), data, GL_DYNAMIC_STORAGE_BIT);
	Buffers::addBuffer(id);
}

