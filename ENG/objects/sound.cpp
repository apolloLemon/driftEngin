#include "sound.h"

SoundENG::SoundENG() {
	sound = irrklang::createIrrKlangDevice();
}

SoundENG::~SoundENG(){
	sound->drop();
}

void SoundENG::Play(int i, bool r){
	if(i>=soundFiles.size()) return;

	sound->play2D(soundFiles[i].c_str(),r);
}