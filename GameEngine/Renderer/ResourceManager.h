#pragma once

#include "Shader.h"
#include <map>

namespace Dread {

class ResourceManager {
public:
	static Shader LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile, const std::string& shaderName);
	static Shader GetShader(const std::string& shaderName);

public:
	static std::map<std::string, Shader> s_Shaders;

private:
	ResourceManager();
	~ResourceManager();


};

}
