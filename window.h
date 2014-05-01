#ifndef PAUNCH_WINDOW_H_
#define PAUNCH_WINDOW_H_

namespace paunch {

std::map<GLFWwindow*, Window*> _glfwToWindow;

void _errorCallback(int error, const char *description);
void _keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void _mouseButtonCallback(GLFWwindow *window, int button, int action, int mod);
void _mousePositionCallback(GLFWwindow *window, double x, double y);
void _mouseEnterWindowCallback(GLFWwindow *window, int entered);
void _windowFocusCallback(GLFWwindow *window, int focused);
void _windowResizeCallback(GLFWwindow *window, int width, int height);

}

#endif // PAUNCH_WINDOW_H_
