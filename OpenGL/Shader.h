#ifndef SHADER_H
#define SHADER_H

#include <glad\glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:

	unsigned int Id;

	Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);

	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMatrix4f(const std::string &name, const GLfloat *value) const;

};

#endif