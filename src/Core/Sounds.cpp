#include "Sounds.h"
#include <AL/al.h>

namespace Template
{

SoundEngine::SoundEngine()
{
	// Initialize OpenAL
	device = alcOpenDevice(nullptr);
	if(!device)
	{
		std::cerr << "Unable to open default OpenAL device." << std::endl;
		return;
	}

	context = alcCreateContext(device, nullptr);
	if(!context)
	{
		std::cerr << "Unable to create OpenAL context." << std::endl;
		alcCloseDevice(device);
		return;
	}
	alcMakeContextCurrent(context);

	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

	// Define parameters for the sine wave
	const ALsizei sampleRate = 44100; // Sample rate
	const ALsizei frequency = 440;    // Frequency in Hz
	const ALsizei duration = 1;       // Duration in seconds
	const ALsizei sampleCount = sampleRate * duration;
	const ALsizei cycles = duration * frequency;
	const ALsizei samplesPerCycle = sampleRate / frequency;
	const ALsizei totalSampleCount = samplesPerCycle * cycles;

	ALshort* samples = new ALshort[totalSampleCount];

	// Generate the sine wave samples
	for(ALsizei i = 0; i < totalSampleCount; ++i)
	{
		samples[i] = 32760 * std::sin(2 * M_PI * frequency * (i + 1) / sampleRate);
		// std::cout << samples[i] << std::endl;
	}
	// std::cout << samples[0] << std::endl;

	alBufferData(buffer, AL_FORMAT_MONO16, samples, totalSampleCount * sizeof(ALshort), sampleRate);

	alSourcei(source, AL_BUFFER, buffer);
	alSourcei(source, AL_LOOPING, 1);

	Init();
}

SoundEngine::~SoundEngine()
{
	delete[] samples;
	alSourceStop(source);
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void SoundEngine::Init()
{
}

void SoundEngine::Play()
{
	if(!playing)
	{
		alSourcePlay(source);
		playing = true;
	}
}
void SoundEngine::Stop()
{
	alSourcePause(source);
	playing = false;
}

void SoundEngine::SetGain()
{
	alSourcef(source, AL_GAIN, gain);
}

void SoundEngine::SetPitch(float pitch)
{
	pitch = glm::mix(minPitch, maxPitch, pitch);
	alSourcef(source, AL_PITCH, pitch);
}

} // namespace Template
