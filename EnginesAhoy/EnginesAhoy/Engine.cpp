#include "Engine.h"
#include <iostream>
#include "TextureManager.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Warrior.h"
#include "Enemy.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"
#include "ParticleEmitter.h"
#include "Parser.h"
#include "Button.h"
#include "SoundManager.h"

Engine* Engine::s_Instance = nullptr;
ParticleEmitter* particleEmitter = nullptr;

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

	if (!MapParser::GetInstance()->Load(1)) {
		std::cout << "Failed to load map" << std::endl;
	}

	if (!MapParser::GetInstance()->Load(2)) {
		std::cout << "Failed to load map" << std::endl;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("level2");

	Parser::GetInstance()->ParseTexture("Assets/textures.tml");
	Parser::GetInstance()->ParseSounds("Assets/sounds.tml");

	SoundManager::GetInstance()->PlayMusik("music2");

	//TextureManager::GetInstance()->Load("player", "Assets/Fumiko.png");

	//TextureManager::GetInstance()->Load("bg", "Assets/bg2.png");
	//Warrior* player = new Warrior(new Properties("player", 500, 200, 24, 32));
	//Enemy* enemy = new Enemy(new Properties("player", 800, 150, 24, 32));

	//Properties* playerProperties = new Properties("player", 500, 200, 24, 32);
	//Properties* enemyProperties = new Properties("player", 800, 150, 24, 32);

	//auto player = ObjectFactory::GetInstance()->CreateObject("player", playerProperties);
	//auto enemy = ObjectFactory::GetInstance()->CreateObject("enemy", enemyProperties);

	//m_GameObjects.push_back(player);
	//m_GameObjects.push_back(enemy);

	Parser::GetInstance()->ParseGameObjects("Assets/level2objects.tml", &m_GameObjects);

	Button* button1 = new Button(20, 20, nullptr, { "button_idle", "button_hover", "button_pressed" });

	m_GameObjects.push_back(button1);

	Camera::GetInstance()->SetTarget(m_GameObjects[0]->GetOrigin()); //Player object needs to be on top of objects list for camera to follow it

	particleEmitter = new ParticleEmitter(DEFAULT);

	return m_IsRunning = true;
}

bool Engine::Clean() {
	TextureManager::GetInstance()->Clean();
	for (int i = 0; i < m_GameObjects.size(); i++) {
		//player->Draw();
		//enemy->Draw();
		m_GameObjects[i]->Clean();
	}
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
	for (int i = 0; i < m_GameObjects.size(); i++) {
		//player->Update(dt);
		//enemy->Update(dt);
		m_GameObjects[i]->Update(dt);
	}
	particleEmitter->UpdateParticles(dt);
	Camera::GetInstance()->Update(dt);

}

void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer,124,218,254,255);

	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("bg2", 0, 0, 1920, 1080, 1.0f, 1.0f, 0.5f);
	m_LevelMap->Render();
	for (int i = 0; i < m_GameObjects.size(); i++) {
		//player->Draw();
		//enemy->Draw();
		m_GameObjects[i]->Draw();
	}

	particleEmitter->RenderParticles();

	SDL_RenderPresent(m_Renderer);

}

SDL_Rect Engine::GetViewPort() {
	return Camera::GetInstance()->GetViewBox();
}

void Engine::Events() {
	Input::GetInstance()->Listen();
}

void Engine::PopState() {
	m_CurrentState = m_GameStates.back();
	m_GameStates.pop_back();
}

void Engine::PushState(GameState* current) {
	m_GameStates.push_back(current);
}

void Engine::ChangeState(GameState* target) {
	PushState(m_CurrentState);
	m_CurrentState = target;
}