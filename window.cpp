#include "paunch.h"
#include "window.h"

namespace paunch {

void InitWindows() {

	if(!glfwInit()) {
		throw Error("Could not initialize GLFW");
	}
}

Window::Window() {}

Window::Window(int width, int height, int nativeWidth, int nativeHeight, bool fullscreen, std::string title) {

	this->size = Int2(width, height);
	this->nativeSize = Int2(nativeWidth, nativeHeight);
	this->title = title;
	this->fullscreen = fullscreen;
	this->actorManagers = std::vector<ActorManager*> {};
}

Window::~Window() {

	glfwDestroyWindow(this->glfw);
	glfwTerminate();
}

void Window::Open() {

	glfwSetErrorCallback(_errorCallback);

	if(this->fullscreen) {
		this->glfw = glfwCreateWindow(this->size.x, this->size.y, this->title.data(), glfwGetPrimaryMonitor(), NULL);
	} else {
		this->glfw = glfwCreateWindow(this->size.x, this->size.y, this->title.data(), NULL, NULL);
	}

	if(this->glfw == NULL) {
		throw Error("Could not initialize window");
	}

	glfwSetKeyCallback(this->glfw, _keyboardCallback);
	glfwSetMouseButtonCallback(this->glfw, _mouseButtonCallback);
	glfwSetCursorPosCallback(this->glfw, _mousePositionCallback);
	glfwSetCursorEnterCallback(this->glfw, _mouseEnterWindowCallback);
	glfwSetWindowFocusCallback(this->glfw, _windowFocusCallback);
	glfwSetWindowSizeCallback(this->glfw, _windowResizeCallback);

	glfwMakeContextCurrent(this->glfw);

	_glfwToWindow[this->glfw] = this;
}

void Window::Close() {

	glfwDestroyWindow(this->glfw);
}

void Window::UpdateDisplay() {

	glfwSwapBuffers(this->glfw);
}

void Window::UpdateEvents() {

	glfwPollEvents();

	for(int i=0; i<GLFW_KEY_LAST; i++) {
		if(this->keyStates[i]) {
			for(auto actorManager: this->actorManagers) {
				actorManager->RunKeyboardEvent(i, Hold);
			}
		}
	}

	Double2 pos = this->GetCursorPosition();
	for(int i=0; i<GLFW_MOUSE_BUTTON_LAST; i++) {
		if(this->mouseButtonStates[i]) {
			for(auto actorManager: this->actorManagers) {
				actorManager->RunMouseButtonEvent(i, Hold, pos.x, pos.y);
			}
		}
	}

	if(this->isJoystick) {
		int size;
		const unsigned char *buttonStates = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &size);
		for(int i=0; i<size; i++) {
			if(buttonStates[i] == GLFW_PRESS) {
				if(this->joyBtnStates[i]) {
					for(auto actorManager: this->actorManagers) {
						actorManager->RunJoystickButtonEvent(i, Hold);
					}
				} else {
					this->joyBtnStates[i] = true;
					for(auto actorManager: this->actorManagers) {
						actorManager->RunJoystickButtonEvent(i, Press);
					}
				}
			} else {
				if(this->joyBtnStates[i]) {
					this->joyBtnStates[i] = false;
					for(auto actorManager: this->actorManagers) {
						actorManager->RunJoystickButtonEvent(i, Release);
					}
				}
			}
		}
	}

	if(this->isJoystick) {
		int size;
		const float *axisStates = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &size);
		for(int i=0; i<size; i++) {
			if(axisStates[i] != this->joyAxisStates[i]) {
				this->joyAxisStates[i] = axisStates[i];
				for(auto actorManager: this->actorManagers) {
					actorManager->RunJoystickAxisEvent(i, (double)this->joyAxisStates[i]);
				}
			}
		}
	}
}

bool Window::ShouldClose() {

	return glfwWindowShouldClose(this->glfw);
}

void Window::SetFullscreen(bool fullscreen) {

	if(this->fullscreen != fullscreen) {
		this->Close();
		this->fullscreen = fullscreen;
		if(this->fullscreen) {
			this->glfw = glfwCreateWindow(this->size.x, this->size.y, this->title.data(), glfwGetPrimaryMonitor(), NULL);
		} else {
			this->glfw = glfwCreateWindow(this->size.x, this->size.y, this->title.data(), NULL, NULL);
		}

		if(this->glfw == NULL) {
			throw Error("Could not switch to fullscreen");
		}

		glfwSetKeyCallback(this->glfw, _keyboardCallback);
		glfwSetMouseButtonCallback(this->glfw, _mouseButtonCallback);
		glfwSetCursorPosCallback(this->glfw, _mousePositionCallback);
		glfwSetCursorEnterCallback(this->glfw, _mouseEnterWindowCallback);
		glfwSetWindowFocusCallback(this->glfw, _windowFocusCallback);
		glfwSetWindowSizeCallback(this->glfw, _windowResizeCallback);

		glfwMakeContextCurrent(this->glfw);

		_glfwToWindow[this->glfw] = this;
	}
}

bool Window::GetFullscreen() {

	return this->fullscreen;
}

Int2 Window::GetSize() {

	return this->size;
}

void Window::SetSize(int width, int height) {

	this->size = Int2(width, height);
	glfwSetWindowSize(this->glfw, width, height);
}

Int2 Window::GetNativeSize() {

	return this->nativeSize;
}

void Window::SetNativeSize(int nativeWidth, int nativeHeight) {

	this->nativeSize = Int2(nativeWidth, nativeHeight);
}

bool Window::GetNativeMouseCorrection() {

	return this->nativeMousePos;
}

void Window::SetNativeMouseCorrection(bool shouldBeNative) {

	this->nativeMousePos = shouldBeNative;
}

void Window::SetActorManagers(std::vector<ActorManager*> actorManagers) {

	this->actorManagers = actorManagers;
}

std::vector<ActorManager*> *Window::GetActorManagers() {

	return &this->actorManagers;
}

Double2 Window::GetCursorPosition() {

	double x, y;
	glfwGetCursorPos(this->glfw, &x, &y);

	Int2 regular = this->GetSize();
	Int2 native = this->GetNativeSize();

	int windHeight;
	if(this->nativeMousePos) {
		x *= ((double)native.x) / ((double)regular.x);
		y *= ((double)native.y) / ((double)regular.y);
		windHeight = native.y;
	} else {
		windHeight = regular.y;
	}

	return Double2(x, windHeight-y);
}

bool Window::CheckForJoystick() {

	if((glfwJoystickPresent(GLFW_JOYSTICK_1) == GL_TRUE) != this->isJoystick) {
		this->isJoystick = !this->isJoystick;
		for(auto actorManager: this->actorManagers) {
			actorManager->RunJoystickDeviceEvent(this->isJoystick);
		}
	}

	return this->isJoystick;
}

bool Window::GetKeyState(int key) {

	return this->keyStates[key];
}

void Window::_setKeyState(int key, bool state) {

	this->keyStates[key] = state;
}

bool Window::GetMouseButtonState(int button) {

	return this->mouseButtonStates[button];
}

void Window::_setMouseButtonState(int button, bool state) {

	this->mouseButtonStates[button] = state;
}

void _errorCallback(int error, const char *description) {

	printf("GLFW Error %i: %s\n", error, description);
	exit(0);
}

void _keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

	if(action == Hold) {
		return;
	}

	_glfwToWindow[window]->_setKeyState(key, action == Press);

	for(auto actorManager: *_glfwToWindow[window]->GetActorManagers()) {
		actorManager->RunKeyboardEvent(key, action);
	}
}

void _mouseButtonCallback(GLFWwindow *window, int button, int action, int mod) {

	Double2 pos = _glfwToWindow[window]->GetCursorPosition();

	_glfwToWindow[window]->_setMouseButtonState(button, action == Press);

	for(auto actorManager: *_glfwToWindow[window]->GetActorManagers()) {
		actorManager->RunMouseButtonEvent(button, action, pos.x, pos.y);
	}
}

void _mousePositionCallback(GLFWwindow *window, double x, double y) {

	Double2 pos = _glfwToWindow[window]->GetCursorPosition();

	for(auto actorManager: *_glfwToWindow[window]->GetActorManagers()) {
		actorManager->RunMousePositionEvent(pos.x, pos.y);
	}
}

void _mouseEnterWindowCallback(GLFWwindow *window, int entered) {

	Double2 pos = _glfwToWindow[window]->GetCursorPosition();

	bool enteredBool = (entered == GL_TRUE);

	for(auto actorManager: *_glfwToWindow[window]->GetActorManagers()) {
		actorManager->RunMouseEnterWindowEvent(pos.x, pos.y, enteredBool);
	}
}

void _windowFocusCallback(GLFWwindow *window, int focused) {

	bool focusedBool = (focused == GL_TRUE);

	for(auto actorManager: *_glfwToWindow[window]->GetActorManagers()) {
		actorManager->RunWindowFocusEvent(focusedBool);
	}
}

void _windowResizeCallback(GLFWwindow *window, int width, int height) {

	_glfwToWindow[window]->SetSize(width, height);

	for(auto actorManager: *_glfwToWindow[window]->GetActorManagers()) {
		actorManager->RunWindowResizeEvent(width, height);
	}

	glViewport(0, 0, width, height);
}

}
