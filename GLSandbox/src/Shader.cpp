#include "Shader.h"

#include <string>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) 
	: m_VertexPath(vertexPath), m_FragmentPath(fragmentPath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(vertexPath, fragmentPath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

ShaderProgramSource Shader::ParseShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	// 1. retieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);

	std::stringstream vShaderStream;
	std::stringstream fShaderStream;

	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();

	return { vShaderStream.str(), fShaderStream.str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    CheckCompileErrors(id, "VERTEX");

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    CheckCompileErrors(program, "PROGRAM");

    glDeleteShader(vs);
    glDeleteShader(fs);

	return program;
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{ 
int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

int Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache.at(name);

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning Uniform '" << name << "' doesn't exist!" << std::endl;

	//m_UniformLocationCache.
	return location;
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(GetUniformLocation(name), (int)value);
}
	// ------------------------------------------------------------------------
	void Shader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(GetUniformLocation(name), value);
	}
	// ------------------------------------------------------------------------
	void Shader::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(GetUniformLocation(name), value);
	}
	// ------------------------------------------------------------------------
	void Shader::SetVec2(const std::string name, glm::vec2& value) const
	{
		glUniform2fv(GetUniformLocation(name), 1, &value[0]);
	}
	// ------------------------------------------------------------------------
	void Shader::SetVec2(const std::string name, float x, float y) const
	{
		glUniform2f(GetUniformLocation(name), x, y);
	}
	// ------------------------------------------------------------------------
	void Shader::SetVec3(const std::string name, glm::vec3& value) const
	{
		glUniform3fv(GetUniformLocation(name), 1, &value[0]);
	}
	// ------------------------------------------------------------------------
	void Shader::SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(GetUniformLocation(name), x, y, z);
	}
	// ------------------------------------------------------------------------
	void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(GetUniformLocation(name), 1, &value[0]);
	}
	void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(GetUniformLocation(name), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
	}

