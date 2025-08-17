#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <glad/glad.h>
#include <algorithm>

struct ShaderProgram {
	GLuint id;
	// Add more fields if needed, like uniform locations, etc.
};

class ShaderManager {
public:
	static ShaderManager& instance();
	ShaderManager(const ShaderManager&) = delete; //do not allow copy constructor for singletons
	ShaderManager& operator=(const ShaderManager&) = delete; //delete copy assignment which is basically the same thing 

	void loadProgram(const std::string& name,
							   const std::string& vert_path,
							   const std::string& frag_path);

	ShaderProgram& getProgram(const std::string& name);

private:
	ShaderManager() = default;
	~ShaderManager();

	std::unordered_map<std::string, ShaderProgram> programs_;

	std::string preprocessGLSL(const std::string& file_path, std::unordered_set<std::string>& seen_includes,
		bool is_root_file);

	GLuint compileShader(GLenum type, const std::string& source);
	//just handles vert and frag for now but will need to expand functionality
	ShaderProgram linkProgram(GLuint vert_shader, GLuint frag_shader);
};