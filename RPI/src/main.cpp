#include <iostream>
#include <cstdio>

extern "C"
{
#include <AL/al.h>
#include <AL/alut.h>
}

using namespace std;

int
main(int argc, char* argv[])
{
	//data structures
	ALuint buffer;
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	//Init subsystem
	alutInit(NULL, NULL);

	//Gen buffer
	alGenBuffers(1, &buffer);
	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	//Load audio file
	alutLoadWAVFile((ALbyte*)"sound.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	//Make a source
	ALuint source1, source2;
	alGenSources(1, &source1);
	alGenSources(1, &source2);
	alSourcei(source1, AL_BUFFER, buffer);
	alSourcei(source2, AL_BUFFER, buffer);

	//Play sound
	getchar();
	alSourcePlay(source1);

	getchar();
	alSourcePlay(source2);
	
	while (1)
		;

	alDeleteBuffers(1, &buffer);
	alDeleteSources(1, &source1);
	alDeleteSources(1, &source2);
	alutExit();
	
	return 0;
}
