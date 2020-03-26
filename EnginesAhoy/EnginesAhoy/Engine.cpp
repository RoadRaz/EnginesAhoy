#include "Engine.h"
#include <iostream>
#include "TextureManager.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Warrior.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG ) != 0) {
		SDL_Log("Failed to initialize SDL subsystems : %s ", SDL_GetError());
		return false;
	}
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	m_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
	
	if (m_Window == nullptr) {
		SDL_Log("Failed to create window : %s ", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create renderer : %s ", SDL_GetError());
		return false;
	}

	SDL_RendererInfo info;
	SDL_GetRendererInfo(m_Renderer, &info);
	std::cout << ("%s", info.name);

	if (MapParser::GetInstance()->Load()) {
		std::cout << "Failed to load map" << std::endl;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("level1");

	TextureManager::GetInstance()->Load("player", "Assets/Fumiko.png");

	TextureManager::GetInstance()->Load("bg", "Assets/bg2.png");

	player = new Warrior(new Properties("player", 500, 100, 24, 32));

	Camera::GetInstance()->SetTarget(player->GetOrigin());

	return m_IsRunning = true;
}

bool Engine::Clean() {
	TextureManager::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
	return true;
}

void Engine::Quit() {
	m_IsRunning = false;
}

void Engine::Update() {
	float dt = Timer::GetInstance()->GetDeltaTime();
	//float dt = SDL_GetTicks();
	//std::cout << std::to_string((dt-ticks)*(60.0f/1000.0f)) << std::endl;
	//std::cout << std::to_string(dt) << std::endl;
	//ticks = dt;
	m_LevelMap->Update();
	player->Update(dt);
	Camera::GetInstance()->Update(dt);
}

void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer,124,218,254,255);

	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("bg", 0, 0, 1920, 1080);
	m_LevelMap->Render();
	player->Draw();

	SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
	Input::GetInstance()->Listen();
}