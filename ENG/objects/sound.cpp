#include "sound.h"

#include <iostream>

SoundENG::SoundENG() {
	sound = irrklang::createIrrKlangDevice();
}

SoundENG::~SoundENG(){
	sound->drop();
}

void SoundENG::Play(int i, bool r, float volume){
	if(i>=soundFiles.size()) return;

	irrklang::ISound* s = sound->play2D(soundFiles[i].c_str(), r, false, true);
	if(s)
		s->setVolume(volume);
}

void SoundENG::Stop(int i)
{
	if (i>=soundFiles.size())	return;

	irrklang::ISoundSource * source = sound->getSoundSource(soundFiles[i].c_str());
	sound->stopAllSoundsOfSoundSource(source);
}