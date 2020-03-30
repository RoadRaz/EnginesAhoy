#pragma once
#ifndef Engine_h
#define Engine_h
#include <SDL.h>
#include <SDL_image.h>
#include "GameMap.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Engine {

public:
	
	static Engine* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}

	bool Init();
	bool Clean();
	void Quit();

	void Update();
	void Render();
	void Events();

	inline bool IsRunning() { return m_IsRunning; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; }
	inline GameMap* GetMap() { return m_LevelMap; }

private:
	
	Engine() {};

	bool m_IsRunning;
	GameMap* m_LevelMap;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	static Engine* s_Instance;
};

#endif //Engine_h