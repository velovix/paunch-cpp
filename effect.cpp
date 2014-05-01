#include "paunch.h"
#include "effect.h"
#include "draw.h"

namespace paunch {

int _checkIfShaderFile(std::string name) {

	std::vector<std::string> texts;
	std::string word;
	for(unsigned int i=0; i<name.length(); i++) {
		if(name.at(i) == '.') {
			word = std::string("");
			continue;
		}
		word += name.at(i);
	}

	if(word.compare("vert") == 0) {
		return Vertex;
	} else if(word.compare("frag") == 0) {
		return Fragment;
	}

	return 0;
}

std::string _loadTextFile(std::string filename) {

	FILE * file = fopen(filename.data(), "r");

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);

	char *data = new char[size];

	rewind(file);
	fread(data, sizeof(char), size, file);

	return std::string(data);
}

GLuint _compileShader(int shaderType, std::vector<std::string> scripts) {

	std::vector<const char*> scriptData;
	for(unsigned int i=0; i<scripts.size(); i++) {
		scriptData.push_back(scripts.at(i).data());
	}

	GLuint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, scripts.size(), &scriptData[0], NULL);
	glCompileShader(shaderID);
	Error error = _checkShaderCompiled(shaderID, shaderType);
	if(error.Report().length() > 0) {
		throw error;
	}

	return shaderID;
}

Error _checkShaderCompiled(GLuint id, int shaderType) {

	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

		char infoLog[infoLogLength+1];
		glGetShaderInfoLog(id, infoLogLength, NULL, &infoLog[0]);

		return Error("Could not compile shader: " + std::string(&infoLog[0]));
	}

	return Error("");
}

void Effect::checkUniformVariable(std::string variable) {

	if(this->uniforms.count(variable) <= 0) {
		this->uniforms[variable] = glGetUniformLocation(this->program, variable.data());
	}
}

Effect::Effect() {

}

Effect::Effect(std::vector<std::string> filenames) {

	GLuint programID = glCreateProgram();

	std::vector<std::string> vscript, fscript;

	for (unsigned int i=0; i<filenames.size(); i++) {
		int shaderType = _checkIfShaderFile(filenames.at(i));
		if(shaderType != 0) {
			std::string text = _loadTextFile(filenames.at(i));
			if(shaderType == Vertex) {
				vscript.push_back(text);
			} else if(shaderType == Fragment) {
				fscript.push_back(text);
			}
		}
	}

	GLuint vshaderID = _compileShader(Vertex, vscript);
	glAttachShader(programID, vshaderID);
	GLuint fshaderID = _compileShader(Fragment, fscript);
	glAttachShader(programID, fshaderID);

	glLinkProgram(programID);
	GLint status;
	glGetProgramiv(programID, GL_LINK_STATUS, &status);
	if(status == GL_FALSE) {
		char programInfoLog[100];
		GLsizei length;
		glGetProgramInfoLog(programID, 100, &length, &programInfoLog[0]);
		throw Error(&programInfoLog[0]);
	}

	this->program = programID;
}

Effect::Effect(std::vector<std::string> scripts, std::vector<int> types) {

	GLuint programID = glCreateProgram();

	std::vector<std::string> vscript, fscript;

	for (unsigned int i=0; i<scripts.size(); i++) {
		if(types.at(i) == Vertex) {
			vscript.push_back(scripts.at(i));
		} else if(types.at(i) == Fragment) {
			fscript.push_back(scripts.at(i));
		}
	}

	GLuint vshaderID = _compileShader(Vertex, vscript);
	glAttachShader(programID, vshaderID);
	GLuint fshaderID = _compileShader(Fragment, fscript);
	glAttachShader(programID, fshaderID);

	Error error = _checkForErrors();
	if(error.Report().length() > 0) {
		throw error;
	}

	glLinkProgram(programID);
	GLint status;
	glGetProgramiv(programID, GL_LINK_STATUS, &status);
	if(status == GL_FALSE) {
		char programInfoLog[100];
		GLsizei length;
		glGetProgramInfoLog(programID, 100, &length, &programInfoLog[0]);
		throw Error(&programInfoLog[0]);
	}

	this->program = programID;
}

void Effect::SetVariablei(std::string variable, int val) {

	this->checkUniformVariable(variable);
	glUniform1i(this->uniforms.at(variable), val);
}

void Effect::SetVariable2i(std::string variable, int val1, int val2) {

	this->checkUniformVariable(variable);
	glUniform2i(this->uniforms.at(variable), val1, val2);
}

void Effect::SetVariable3i(std::string variable, int val1, int val2, int val3) {

	this->checkUniformVariable(variable);
	glUniform3i(this->uniforms.at(variable), val1, val2, val3);
}

void Effect::SetVariable4i(std::string variable, int val1, int val2, int val3, int val4) {

	this->checkUniformVariable(variable);
	glUniform4i(this->uniforms.at(variable), val1, val2, val3, val4);
}

void Effect::SetVariableui(std::string variable, unsigned int val) {

	this->checkUniformVariable(variable);
	glUniform1ui(this->uniforms.at(variable), val);
}

void Effect::SetVariable2ui(std::string variable, unsigned int val1, unsigned int val2) {

	this->checkUniformVariable(variable);
	glUniform2ui(this->uniforms.at(variable), val1, val2);
}

void Effect::SetVariable3ui(std::string variable, unsigned int val1, unsigned int val2, unsigned int val3) {

	this->checkUniformVariable(variable);
	glUniform3ui(this->uniforms.at(variable), val1, val2, val3);
}

void Effect::SetVariable4ui(std::string variable, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4) {

	this->checkUniformVariable(variable);
	glUniform4ui(this->uniforms.at(variable), val1, val2, val3, val4);
}

void Effect::SetVariablef(std::string variable, float val) {

	this->checkUniformVariable(variable);
	glUniform1f(this->uniforms.at(variable), val);
}

void Effect::SetVariable2f(std::string variable, float val1, float val2) {

	this->checkUniformVariable(variable);
	glUniform2f(this->uniforms.at(variable), val1, val2);
}

void Effect::SetVariable3f(std::string variable, float val1, float val2, float val3) {

	this->checkUniformVariable(variable);
	glUniform3f(this->uniforms.at(variable), val1, val2, val3);
}

void Effect::SetVariable4f(std::string variable, float val1, float val2, float val3, float val4) {

	this->checkUniformVariable(variable);
	glUniform4f(this->uniforms.at(variable), val1, val2, val3, val4);
}

GLuint Effect::getProgramID() {

	return this->program;
}

void UseEffect(Effect *effect) {

	glUseProgram(effect->getProgramID());

	Error error = _checkForErrors();
	if(error.Report().length() > 0) {
		throw error;
	}
}

void DisableEffects() {

	glUseProgram(0);
}

}
