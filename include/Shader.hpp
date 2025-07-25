#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <algorithm>

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertex_path, const char* fragment_path);

	void use();

	void setBool(const std::string& name, bool val) const;
	void setInt(const std::string& name, int val) const;
	void setFloat(const std::string& name, float val) const;
private:
	void checkCompileErrors(GLint shader, std::string type);
	std::string preprocessGLSL(const std::string& file_path,
							   std::unordered_set<std::string>& seen_includes,
							   bool is_root_file);
};
#endif // !SHADER_H
