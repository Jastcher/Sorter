#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

ShaderProgramSource GetGraphShader(const std::string& eq);
ShaderProgramSource GetFileContents(const char* filename);

class Shader
{
  public:
	GLuint ID;
	Shader();
	Shader(const char* vertex, const char* fragment);
	Shader(const char* fileName);

	void Create(const char* vertex, const char* fragment, const char* fileName = "graph.shader");

	void Activate() const;
	void Delete();
	void SetInt(const char* uniform, int unit);
	void SetFloat(const char* uniform, float unit);
	void SetVec2(const char* uniform, glm::vec2 unit);
	void SetVec3(const char* uniform, glm::vec3 unit);
	void SetVec4(const char* uniform, glm::vec4 unit);
	void SetMat4(const char* uniform, glm::mat4 unit) const;

  private:
	void CompileErrors(unsigned int shader, const char* type, const char* shaderName);
};
