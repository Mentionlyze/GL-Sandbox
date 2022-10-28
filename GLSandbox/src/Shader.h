#pragma once

#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Renderer.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:
	std::string m_VertexPath;
	std::string m_FragmentPath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void Bind() const;
	void Unbind() const;


private:
	ShaderProgramSource ParseShader(const std::string& vertexPath, const std::string& fragmentPath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	void CheckCompileErrors(unsigned int shader, std::string type);
	int GetUniformLocation(const std::string& name) const;

public:
	// utility uniform functions
	  // ------------------------------------------------------------------------
	void SetBool(const std::string& name, bool value) const;
	// ------------------------------------------------------------------------
	void SetInt(const std::string& name, int value) const;
	// ------------------------------------------------------------------------
	void SetFloat(const std::string& name, float value) const;
	// ------------------------------------------------------------------------
	void SetVec2(const std::string name, glm::vec2& value) const;
	// ------------------------------------------------------------------------
	void SetVec2(const std::string name, float x, float y) const;
	// ------------------------------------------------------------------------
	void SetVec3(const std::string name, glm::vec3& value) const;
	// ------------------------------------------------------------------------
	void SetVec3(const std::string& name, float x, float y, float z) const;
	// ------------------------------------------------------------------------
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	// ------------------------------------------------------------------------
	void SetVec4(const std::string& name, float x, float y, float z, float w) const;
	// ------------------------------------------------------------------------
	void SetMat2(const std::string& name, const glm::mat2& mat) const;
	// ------------------------------------------------------------------------
	void SetMat3(const std::string& name, const glm::mat3& mat) const;
	// ------------------------------------------------------------------------
	void SetMat4(const std::string& name, const glm::mat4& mat) const;
};

