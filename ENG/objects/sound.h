#pragma once
#include "ENG/includes/IrrKlang/irrKlang.h"
#include <vector>
#include <string>

class SoundENG  {
public:
	SoundENG();
	~SoundENG();
	void Play(int i, bool r);
	irrklang::ISoundEngine * sound;
	std::vector<std::string> soundFiles;

	
};