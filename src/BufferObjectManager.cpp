#include "BufferObjectManager.hpp"

BufferObjectManager::BufferObjectManager() = default; //singleton yn?

BufferObjectManager::~BufferObjectManager() {
	// have the option to store just the values 
	
	for (const auto& pair : buffers_) {
		glDeleteBuffers(1, pair.second); 
	}
	//	glDeleteBuffersARB() is this the same thing
}
void BufferObjectManager::addVAO(GLuint &vao) const{

}
void BufferObjectManager::addVBO(GLuint &vbo) const{

}
void BufferObjectManager::addEBO(GLuint &ebo) const{

}