#include "ShaderManager.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

//singleton constructor
ShaderManager& ShaderManager::instance() {
	static ShaderManager instance;
	return instance;
}

ShaderManager::~ShaderManager() {
	for (auto& entry : programs_) {
		if (entry.second.id) glDeleteProgram(entry.second.id);
	}
}

ShaderProgram& ShaderManager::getProgram(const std::string& name) {
	auto it = programs_.find(name);
	if (it == programs_.end()) throw std::runtime_error("couldnt get program : " + name);
	return it->second;
}

//lowk this doesnt need to return anything if it just loads to programs_ cuz i can just call getter 
void ShaderManager::loadProgram(
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
	std::string vertTxt = preprocessGLSL(vert_path, vertIncludes, true);
	std::string fragTxt = preprocessGLSL(frag_path, fragIncludes, true);

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
std::string ShaderManager::preprocessGLSL(
	const std::string& file_path,
	std::unordered_set<std::string>& seen_includes, bool is_root_file)
{
	//replace backslashed with forward slashed so GLSL doesn't process as escape
	std::string fixedPath = file_path;
	std::replace(fixedPath.begin(), fixedPath.end(), '\\', '/');

	if (seen_includes.count(file_path)) return ""; //if we have already processed this include
	seen_includes.insert(file_path);
	std::ifstream file(file_path);
	if (!file.is_open()) throw std::runtime_error("Cannot open file : " + file_path);

	std::stringstream body;
	std::string versionLine;
	std::string line;

	while (std::getline(file, line)) {
		if (line.rfind("#version", 0) == 0) {
			if (is_root_file) {
				versionLine = line + "\n";
			}
		} else if (line.rfind("#include", 0) == 0) { //if it finds include at the start of the line
			//grab whatever is in the include
			auto start = line.find('"') + 1;
			auto end = line.find('"', start); 
			std::string include = line.substr(start, end - start);
			body << preprocessGLSL(include, seen_includes, false);
		}
		else {
			body << line << "\n";
		}
	}
	std::stringstream final;
	if (!versionLine.empty()) final << versionLine;
	final << "#line 1\n";
	final << body.str();

	return final.str(); //might need to be a c_str we shall see
	//maybe do it here instead of compile shader
}

GLuint ShaderManager::compileShader(GLenum type, const std::string& source) {
	GLuint shader = glCreateShader(type);
	/*std::cout << "glCreateShader ptr: " << (void*)glCreateShader << std::endl;
	std::cout << "Compiling shader:\n" << source << "\n---" << std::endl;
	std::cout << "Type: " << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << std::endl;*/


	//// Display shader type to console
	//const char* shaderTypeStr = nullptr;
	//switch (type) {
	//	case GL_VERTEX_SHADER: shaderTypeStr = "Vertex Shader"; break;
	//	case GL_FRAGMENT_SHADER: shaderTypeStr = "Fragment Shader"; break;
	//	case GL_GEOMETRY_SHADER: shaderTypeStr = "Geometry Shader"; break;
	//	case GL_COMPUTE_SHADER: shaderTypeStr = "Compute Shader"; break;
	//	case GL_TESS_CONTROL_SHADER: shaderTypeStr = "Tessellation Control Shader"; break;
	//	case GL_TESS_EVALUATION_SHADER: shaderTypeStr = "Tessellation Evaluation Shader"; break;
	//	default: shaderTypeStr = "Unknown Shader Type"; break;
	//}
	//std::cout << "Created shader of type: " << shaderTypeStr << std::endl;

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
		std::cerr << "shader compile error in :" << source << "\n" << log << std::endl; //specify enum name
		throw std::runtime_error("failed to compile shader");
	}
	return shader;
}

ShaderProgram ShaderManager::linkProgram(GLuint vert_shader, GLuint frag_shader) {
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
