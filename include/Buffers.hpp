#include <unordered_map>
#include <string>
#include <glad/glad.h>
#include "Types/BufferTypes.hpp"

//will need to interact with models n such
namespace Buffers {
	extern std::unordered_map<std::string, GLuint> g_buffers;

	void configureBuffers(); //misc initial implementation shit thatll change a lot
	
	void addBuffer(std::string name, GLuint id); // idk if its a reference to the id or just the id
	void bind();
	void unbind();
	void destroy();
	void setData(const void* data, GLsizeiptr bytes, GLenum usage = GL_STATIC_DRAW);
	GLuint& getBuffer(std::string name);
	//std::unordered_map<std::string, GLuint> getBuffers(); //wont let me return a reference
}