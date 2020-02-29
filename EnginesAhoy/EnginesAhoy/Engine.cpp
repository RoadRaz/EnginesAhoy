#include "Engine.h"
#include <iostream>

Engine* Engine::s_instance = nullptr;

bool Engine::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL subsystems : %s ", SDL_GetError());
		return false;
	}

	return m_IsRunning = true;
}

bool Engine::Clean() {
	return true;
}

void Engine::Quit() {

}

void Engine::Update() {
	SDL_Log("Update Log...");
}

void Engine::Render() {

}

void Engine::Events() {

}