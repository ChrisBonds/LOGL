#include "Shader.hpp"
#include "Shaders.hpp"


Shader::Shader(const char* vertex_path, const char* fragment_path) {
	//huge ass constructor
	std::unordered_set<std::string> vertIncludes;
	std::unordered_set<std::string> fragIncludes;
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		//if this works first try im goated
		/*vShaderFile.open(vertex_path);
		fShaderFile.open(fragment_path);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();*/

		vertexCode = preprocessGLSL(vertex_path, vertIncludes, true);
		fragmentCode = preprocessGLSL(fragment_path, fragIncludes, true);
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL); //not sure this is allowed to be null
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL); //not sure this is allowed to be null
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
};
void Shader::use() {
	glUseProgram(ID);
}
void Shader::setBool(const std::string& name, bool val) const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)val);
}
void Shader::setInt(const std::string& name, int val) const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
}
void Shader::setFloat(const std::string& name, float val) const{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
}
void Shader::setMat4(const std::string& name, glm::mat4 val)const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}
void Shader::setVec3(const std::string& name, glm::vec3 val)const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1,  glm::value_ptr(val));
}

void Shader::checkCompileErrors(GLint shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type : " << type << "\n" << infoLog << "\n\n";
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type : " << type << "\n" << infoLog << "\n\n";
		}
	}
}

std::string Shader::preprocessGLSL(
	//change to std::filepath later
	const std::string& file_path,
	std::unordered_set<std::string>& seen_includes, bool is_root_file)
{
	//replace backslashed with forward slashed so GLSL doesn't process as escape
	//std::string fixedPath = file_path;
	std::filesystem::path path(file_path);
	if (!path.is_absolute()) {
		path = shaderBaseDir / path;
	}
	path = std::filesystem::weakly_canonical(path);
	std::string fixedPath = path.string();
	std::replace(fixedPath.begin(), fixedPath.end(), '\\', '/');

	if (seen_includes.count(fixedPath)) return "";
	seen_includes.insert(fixedPath);

	std::ifstream file(path);
	if (!file.is_open()) throw std::runtime_error("Cannot open file : " + file_path);

	std::stringstream body;
	std::string versionLine;
	std::string line;

	while (std::getline(file, line)) {
		if (line.rfind("#version", 0) == 0) {
			if (is_root_file) {
				versionLine = line + "\n";
			}
		}
		else if (line.rfind("#include", 0) == 0) { //if it finds include at the start of the line
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