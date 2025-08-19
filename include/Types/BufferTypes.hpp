#include <string>
#include <glad/glad.h>

//fixed size immutable vs variable sized mutable dilemma


//	Buffer Binding Target	Purpose
//	GL_ARRAY_BUFFER					Vertex attributes
//	GL_ATOMIC_COUNTER_BUFFER		Atomic counter storage
//	GL_COPY_READ_BUFFER				Buffer copy source
//	GL_COPY_WRITE_BUFFER			Buffer copy destination
//	GL_DISPATCH_INDIRECT_BUFFER		Indirect compute dispatch commands
//	GL_DRAW_INDIRECT_BUFFER			Indirect command arguments
//	GL_ELEMENT_ARRAY_BUFFER			Vertex array indices
//	GL_PIXEL_PACK_BUFFER			Pixel read target
//	GL_PIXEL_UNPACK_BUFFER			Texture data source
//	GL_QUERY_BUFFER					Query result buffer
//	GL_SHADER_STORAGE_BUFFER		Read - write storage for shaders
//	GL_TEXTURE_BUFFER				Texture data buffer
//	GL_TRANSFORM_FEEDBACK_BUFFER	Transform feedback buffer
//	GL_UNIFORM_BUFFER				Uniform block storage

struct VAO { //init first 
	std::string Name;
	GLuint id;
	unsigned int BindingPoint = 0;

	void Init(std::string name = "default");
};
struct VBO { //init second 
	std::string Name; //	?
	GLuint id;
	GLsizeiptr Size = 0;
	unsigned int Stride;
	//GLsizeiptr Capacity;

	void Init(const void* data, unsigned int stride, GLenum usage = GL_STATIC_DRAW, std::string name = "default");
	//void setData(const void* data, GLsizeiptr bytes, GLenum usage = GL_STATIC_DRAW);
	//void destroy();
};
struct EBO { //init third 
	std::string Name;
	GLuint id;
	GLsizeiptr Size = 0;

	void Init(const void* data, std::string name = "default");
	//void setData();
	//void destroy();
};
