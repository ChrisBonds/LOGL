#include "Types/BufferTypes.hpp"
#include "Buffers.hpp"

void VAO::Init(std::string name) {
	//we dont know the data inside it 
	Name = name + "VAO"; //lol
	glCreateVertexArrays(1, &VAOid);
	Buffers::addBuffer(VAOid);
	//pretty sure this is all i need if im using DSA
}
void VBO::Init(const void* data, GLenum usage, std::string name) {
	Name = name + "VBO";
	Size = sizeof(data); //not correct
	glCreateBuffers(1, &VBOid); //2nd param is location of names to be stored so could use g_buffers
	glNamedBufferStorage(VBOid, Size, data, GL_DYNAMIC_STORAGE_BIT); //dynamic storage bit indicates buffer data can be changed but not size
	//might need to use glBufferStorage
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	//i think i just need the pointer to the id not the type or anything else like that		
	Buffers::addBuffer(VBOid);
}
void EBO::Init(const void* data, std::string name) {
	Name = name + "EBO";
	glCreateBuffers(1, &EBOid);
	glNamedBufferStorage(EBOid, sizeof(data), data, GL_DYNAMIC_STORAGE_BIT);
	Buffers::addBuffer(EBOid);
}

