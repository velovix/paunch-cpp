#include "paunch.h"

namespace paunch {

std::string _getGLErrorString(GLuint code) {

	switch(code) {
	case GL_INVALID_ENUM:
		return std::string("GL_INVALID_ENUM");
	case GL_INVALID_VALUE:
		return std::string("GL_INVALID_VALUE");
	case GL_INVALID_OPERATION:
		return std::string("GL_INVALID_OPERATION");
	case GL_STACK_OVERFLOW:
		return std::string("GL_STACK_OVERFLOW");
	case GL_STACK_UNDERFLOW:
		return std::string("GL_STACK_UNDERFLOW");
	case GL_OUT_OF_MEMORY:
		return std::string("GL_OUT_OF_MEMORY");
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return std::string("GL_INVALID_FRAMEBUFFER_OPERATION");
	default:
		return std::string("unknown error");
	}
}

Error _checkForErrors() {

	std::string error = "OpenGL Error(s): ";
	GLuint errNumb = glGetError();
	int errCnt = 0;
	while(errNumb != GL_NO_ERROR && errCnt < 10) {
		error.append(_getGLErrorString(errNumb));
		error.append(" ");
		errCnt++;
	}

	if(errCnt == 0) {
		return Error("");
	}

	return Error(error);
}

void InitDraw() {

	if(glewInit() != 0) {
		throw Error("Could not initialize OpenGL");
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Clear() {

	glClear(GL_COLOR_BUFFER_BIT);
}

}
