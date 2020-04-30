#pragma once
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H
#include <map>
#include <string>
#include <iostream>
#include <SDL_mixer.h>

#define FREQ 44100
#define CHUNK_SIZE 2048

using EffectMap = std::map<std::string, Mix_Chunk*>;
using MusikMap = std::map<std::string, Mix_Music*>;

class SoundManager {
public:
	void Clean();

	void PlayMusik(std::string id);
	void LoadMusik(std::string id, std::string source);

	void PlayEffect(std::string id);
	void LoadEffect(std::string id, std::string source);

	inline static SoundManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new SoundManager(); }

private:
	SoundManager();
	MusikMap m_MusicMap;
	EffectMap m_EffectMap;
	static SoundManager* s_Instance;
};
#endif