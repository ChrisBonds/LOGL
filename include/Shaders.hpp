#include "Shader.hpp"
#include <unordered_map>
#include<string>

namespace Shaders {
	extern std::unordered_map<std::string, std::unique_ptr<Shader>> g_Shaders;
	void initShaders(); //the dirty prototyping function
	Shader& getShader(std::string name);
}