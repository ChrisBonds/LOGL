#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//shaders namespace to iterate on shape of shaders in program
//really starting not not like the design of this guy
class Shader {
public:
	GLuint ID;
	static inline std::filesystem::path shaderBaseDir = R"(res\shaders\OpenGL)";

	Shader(const char* vertex_path, const char* fragment_path, std::string name);

	void use();

	void setBool(const std::string& name, bool val) const;
	void setInt(const std::string& name, int val) const;
	void setFloat(const std::string& name, float val) const;
	void setMat4(const std::string& name, glm::mat4 val)const;

private:
	static void checkCompileErrors(GLint shader, std::string type);
	static std::string preprocessGLSL(const std::string& file_path,
							   std::unordered_set<std::string>& seen_includes,
							   bool is_root_file);
};
#endif // !SHADER_H
