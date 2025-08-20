#include "ResourceManager.h"

namespace Dread {

std::map<std::string, Shader> ResourceManager::s_Shaders;


Shader ResourceManager::LoadShader(const std::string &vertexShaderFile, const std::string &fragmentShaderFile, const std::string &shaderName) {
	Shader shader(vertexShaderFile, fragmentShaderFile);
	s_Shaders[shaderName] = shader;
	return shader;
}

Shader ResourceManager::GetShader(const std::string &shaderName) {
	return s_Shaders[shaderName];
}

}
