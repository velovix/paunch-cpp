#ifndef PAUNCH_EFFECT_H_
#define PAUNCH_EFFECT_H_

namespace paunch {

int _checkIfShaderFile(std::string);
std::string _loadTextFile();
GLuint _compileShader(int shaderType, std::vector<std::string> scripts);
Error _checkShaderCompiled(GLuint id, int shaderType);

}

#endif // PAUNCH_EFFECT_H_
