#include "paunch.h"

namespace paunch {

ActorManager::ActorManager() {

	this->actors = std::vector<Actor*> {};
}

void ActorManager::SetActors(std::vector<Actor*> actors) {

	this->actors = actors;
}

std::vector<Actor*> *ActorManager::GetActors() {

	return &this->actors;
}

void ActorManager::RunKeyboardEvent(int key, int action) {

	for(auto &val: this->actors) {
		val->OnKeyboard(key, action);
	}
}

void ActorManager::RunMouseButtonEvent(int button, int action, double x, double y) {

	for(auto &val: this->actors) {
		val->OnMouseButton(button, action, x, y);
	}
}

void ActorManager::RunMousePositionEvent(double x, double y) {

	for(auto &val: this->actors) {
		val->OnMousePosition(x, y);
	}
}

void ActorManager::RunWindowResizeEvent(int width, int height) {

	for(auto &val: this->actors) {
		val->OnWindowResize(width, height);
	}
}

void ActorManager::RunMouseEnterWindowEvent(double x, double y, bool entered) {

	for(auto &val: this->actors) {
		val->OnMouseEnterWindow(x, y, entered);
	}
}

void ActorManager::RunWindowFocusEvent(bool focused) {

	for(auto &val: this->actors) {
		val->OnWindowFocus(focused);
	}
}

void ActorManager::RunJoystickButtonEvent(int button, int action) {

	for(auto &val: this->actors) {
		val->OnJoystickButton(button, action);
	}
}

void ActorManager::RunJoystickAxisEvent(int device, double value) {

	for(auto &val: this->actors) {
		val->OnJoystickAxis(device, value);
	}
}

void ActorManager::RunJoystickDeviceEvent(bool connected) {

	for(auto &val: this->actors) {
		val->OnJoystickDevice(connected);
	}
}

void ActorManager::RunCollisionEvent() {

	for(auto &val: this->actors) {

		std::vector<Collider*> colliders1 = val->GetColliders();
		if(colliders1.size() == 0) {
			continue;
		}

		for(auto &val2: this->actors) {
			if(val == val2) {
				continue;
			}

			std::vector<Collider*> colliders2 = val2->GetColliders();
			for(auto &c1: colliders1) {
				for(auto &c2: colliders2) {
					if(!c1->Collides(*c2)) {
						continue;
					}

					val->OnCollision(c1, c2, val);
				}
			}
		}
	}
}

void ActorManager::RunTickEvent() {

	for(auto &val: this->actors) {
		val->OnTick();
	}
}

void ActorManager::RunDrawEvent() {

	for(auto &val: this->actors) {
		val->OnDraw();
	}
}

}
