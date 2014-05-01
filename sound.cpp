#include "paunch.h"
#include "stb_vorbis.c"

namespace paunch {

Sound::Sound() {
	
}

Sound::Sound(std::string filename) {

	short int *data;
	int size;
	if((size = stb_vorbis_decode_filename((char*)filename.data(), &this->numChannels, &data)) == -1) {
		throw Error("Invalid OGG file");
	}

	alGenSources(1, &this->source);
	alGenBuffers(1, &this->buffer);

	if(this->numChannels == 1) {
		alBufferData(this->buffer, AL_FORMAT_MONO16, data, size*sizeof(short int)*this->numChannels, 44100);
	} else if(this->numChannels == 2) {
		alBufferData(this->buffer, AL_FORMAT_STEREO16, data, size*sizeof(short int)*this->numChannels, 44100);
	} else {
		throw Error("Invalid channel count in OGG file");
	}

	alSourcei(this->source, AL_BUFFER, this->buffer);

	free(data);
}

Sound::~Sound() {

	alDeleteSources(1, &this->source);
	alDeleteBuffers(1, &this->buffer);
}

void Sound::Play() {

	alSourcePlay(this->source);
}

void Sound::Pause() {

	alSourcePause(this->source);
}

void Sound::Stop() {

	alSourceStop(this->source);
}

void Sound::SetLoop(bool loop) {

	if(loop) {
		alSourcei(this->source, AL_LOOPING, AL_TRUE);
	} else {
		alSourcei(this->source, AL_LOOPING, AL_FALSE);
	}
}

int Sound::GetState() {

	int state;
	alGetSourcei(this->source, AL_SOURCE_STATE, &state);
	return state;
}

float Sound::GetGain() {

	float gain;
	alGetSourcef(this->source, AL_GAIN, &gain);
	return gain;
}

void Sound::SetGain(float gain) {

	alSourcef(this->source, AL_GAIN, gain);
}

}
