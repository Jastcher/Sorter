#pragma once
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <thread>
#include <cmath>
#include "glm/glm.hpp"

namespace Template
{

class SoundEngine
{
  public:
	SoundEngine();
	~SoundEngine();

	void SetPitch(float pitch);
	void SetGain();

	void Init();

	void Play();
	void Stop();

	float minPitch = 0.2f;
	float maxPitch = 1.0f;
	float gain = 1.0f;

  private:
	bool playing = false;

	ALshort* samples;
	ALCdevice* device;
	ALCcontext* context;

	int sampleRate = 44100; // samples per second

	ALuint buffer;
	ALuint source;
};

} // namespace Template
