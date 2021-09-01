#pragma once
#include <string>
#include <unordered_map>

#include "glm/gtc/type_ptr.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	//TODO colocar os outros tipos de uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform1i(const std::string& name, int v0);
	void SetUniformMatrix4fv(const std::string& name,int count, bool transpose, const float* value);
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	ShaderProgramSource ParseShader(const std::string& filepath);
	int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int GetUniformLocation(const std::string& name);
};
