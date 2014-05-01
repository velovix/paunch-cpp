#include "paunch.h"

namespace paunch {

Audio::Audio() {

	this->device = alcOpenDevice(NULL);
	if(this->device == NULL) {
		throw Error("Could not open audio device");
	}

	this->context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(this->context);
}

Audio::~Audio() {

	this->context = alcGetCurrentContext();
	this->device = alcGetContextsDevice(this->context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(this->context);
	alcCloseDevice(this->device);
}

}
