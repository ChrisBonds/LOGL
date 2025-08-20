#include "Shader.hpp"
#include <unordered_map>
#include<string>

namespace Shaders {
	//extern std::unordered_map<std::string, std::unique_ptr<Shader>> g_Shaders; //g_Shaders gains ownership of eavh shader object but idk yet if heap error comes from deleting g_shaders or if default ~shader() is called. pretty sure ts a double delete.
	extern std::unordered_map<std::string, std::unique_ptr<Shader>> g_Shaders;
	void initShaders(); //the dirty prototyping function
	Shader& getShader(std::string name);
}