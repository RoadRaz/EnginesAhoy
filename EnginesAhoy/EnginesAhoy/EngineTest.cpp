//#include "Engine.h"
//#include <iostream>
//#include "TextureManager.h"
//#include "Vector2D.h"
//#include "Transform.h"
//#include "Warrior.h"
//#include "Enemy.h"
//#include "Input.h"
//#include "Timer.h"
//#include "MapParser.h"
//#include "Camera.h"
//#include "ParticleEmitter.h"
//#include "Parser.h"
//#include "Button.h"
//#include "SoundManager.h"
//#include "LevelManager.h"
//
//Engine* Engine::s_Instance = nullptr;
//ParticleEmitter* particleEmitter = nullptr;
//
//bool Engine::Init() {
//	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
//		SDL_Log("Failed to initialize SDL subsystems : %s ", SDL_GetError());
//		return false;
//	}
//	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
//
//	m_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
//
//	if (m_Window == nullptr) {
//		SDL_Log("Failed to create window : %s ", SDL_GetError());
//		return false;
//	}
//
//	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//
//	if (m_Renderer == nullptr) {
//		SDL_Log("Failed to create renderer : %s ", SDL_GetError());
//		return false;
//	}
//
//	SDL_RendererInfo info;
//	SDL_GetRendererInfo(m_Renderer, &info);
//	std::cout << ("%s", info.name);
//
//	LevelManager::GetInstance()->Init(1);
//	return m_IsRunning = true;
//}
//
//bool Engine::Clean() {
//	TextureManager::GetInstance()->Clean();
//	for (int i = 0; i < m_GameObjects.size(); i++) {
//		//player->Draw();
//		//enemy->Draw();
//		m_GameObjects[i]->Clean();
//	}
//	SDL_DestroyRenderer(m_Renderer);
//	SDL_DestroyWindow(m_Window);
//	IMG_Quit();
//	SDL_Quit();
//	return true;
//}
//
//void Engine::Quit() {
//	m_IsRunning = false;
//}
//
//void Engine::Update() {
//	LevelManager::GetInstance()->Update();
//}
//
//void Engine::Render() {
//	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
//
//	SDL_RenderClear(m_Renderer);
//
//	LevelManager::GetInstance()->Render();
//	SDL_RenderPresent(m_Renderer);
//
//}
//
//SDL_Rect Engine::GetViewPort() {
//	return Camera::GetInstance()->GetViewBox();
//}
//
//void Engine::Events() {
//	Input::GetInstance()->Listen();
//}
//
//void Engine::PopState() {
//	m_CurrentState = m_GameStates.back();
//	m_GameStates.pop_back();
//}
//
//void Engine::PushState(GameState* current) {
//	m_GameStates.push_back(current);
//}
//
//void Engine::ChangeState(GameState* target) {
//	PushState(m_CurrentState);
//	m_CurrentState = target;
//}