#pragma once
#include "ENG/includes/IrrKlang/irrKlang.h"
#include <vector>
#include <string>

class SoundENG  {
public:
	SoundENG();
	~SoundENG();
	void Play(int i, bool r, float volume = 1.0f);
	void Stop(int i);
	irrklang::ISoundEngine * sound;
	std::vector<std::string> soundFiles;
	
};