#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Dread {

class Shader {
public:
	Shader() {}
	Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath);
	void Bind();
	void UnBind();
	void SetUniformMatrix4f(const std::string &uniformName, glm::mat4 matrix);
	void SetUniformMatrix3f(const std::string &uniformName, glm::mat3 matrix);
	void SetUniformVec4f(const std::string &uniformName, glm::vec4 vector4);
	void SetUniformVec3f(const std::string &uniformName, glm::vec3 vector3);
	void SetUniformVec2f(const std::string &uniformName, glm::vec2 vector2);
	void SetUniformInt(const std::string &uniformName, int value);
	void SetUniformFloat(const std::string &uniformName, float value);
	unsigned int GetRendererId() { return m_RendererId; }

private:
	void checkShaderCompilationStatus(unsigned int shader, const std::string &shaderName);
	void checkShaderProgramLinkStatus(unsigned int shaderProgram);
	void createShader(const std::string vertexPath, const std::string fragmentPath);

private:
	unsigned int m_RendererId;
};

}
