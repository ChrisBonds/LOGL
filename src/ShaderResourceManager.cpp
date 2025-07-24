#include "ShaderResourceManager.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

//singleton constructor
ShaderResourceManager& ShaderResourceManager::instance() {
	static ShaderResourceManager instance;
	return instance;
}

ShaderResourceManager::~ShaderResourceManager() {
	for (auto& entry : programs_) {
		if (entry.second.id) glDeleteProgram(entry.second.id);
	}
}

ShaderProgram& ShaderResourceManager::getProgram(const std::string& name) {
	auto it = programs_.find(name);
	if (it == programs_.end()) throw std::runtime_error("couldnt get program : " + name);
	return it->second;
}

//lowk this doesnt need to return anything if it just loads to programs_ cuz i can just call getter 
void ShaderResourceManager::loadProgram(
	const std::string& name,
	const std::string& vert_path,
	const std::string& frag_path) 
{
	auto it = programs_.find(name);
	if (it != programs_.end()) {
		std::cout << "program : " << name << " already exists in _programs" << std::endl;
		return;
	}

	std::unordered_set<std::string> vertIncludes;
	std::unordered_set<std::string> fragIncludes;
	std::string vertTxt = preprocessGLSL(vert_path, vertIncludes);
	std::string fragTxt = preprocessGLSL(vert_path, fragIncludes);

	GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertTxt);
	GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragTxt);

	//link program
	ShaderProgram program = linkProgram(vertShader, fragShader);
	programs_.emplace(name, program); //insert if key doesnt exist
	std::cout << "succesfully loaded " << name << " to _programs" << std::endl;
	return;
}

//just gonna put the set before i call the function so i have a map of includes per shader object 
//also will need 1 set per file not per object
//should also include checking for correct file extension
std::string ShaderResourceManager::preprocessGLSL(
	const std::string& file_path,
	std::unordered_set<std::string>& seen_includes)
{
	if (seen_includes.count(file_path)) return ""; //if we have already processed this include
	std::ifstream file(file_path);
	if (!file.is_open()) throw std::runtime_error("Cannot open file : " + file_path);

	std::stringstream out;
	out << "#line 1 \"" << file_path << "\"\n"; //little confused by this
	std::string line;
	while (std::getline(file, line)) {
		if (line.rfind("#include", 0) == 0) { //if it finds include at the start of the line
			//grab whatever is in the include
			auto start = line.find('"') + 1;
			auto end = line.find('"', start); 
			std::string include = line.substr(start, end - start);
			out << preprocessGLSL(include, seen_includes);
		}
		else {
			out << line << "\n";
		}
	}
	return out.str(); //might need to be a c_str we shall see
	//maybe do it here instead of compile shader
}

GLuint ShaderResourceManager::compileShader(GLenum type, const std::string& source) {
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		std::string log(logLen, ' '); //odd line
		glGetShaderInfoLog(shader, logLen, nullptr, &log[0]); //also off
		std::cerr << "shader compile error : \n" << log << std::endl; //specify enum name
		throw std::runtime_error("failed to compile shader");
	}
	return shader;
}

ShaderProgram ShaderResourceManager::linkProgram(GLuint vert_shader, GLuint frag_shader) {
	GLuint program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLint logLen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
		std::string log(logLen, ' ');
		glGetProgramInfoLog(program, logLen, nullptr, &log[0]);
		std::cerr << "program link error : \n" << log << std::endl;
		throw std::runtime_error("failed to link shader program");
	}
	//mr clean
	glDetachShader(program, vert_shader);
	glDetachShader(program, frag_shader);
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	ShaderProgram sp{}; //could write a little init method but i think we r good for now
	sp.id = program;
	return sp;
}
