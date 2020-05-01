#include "LevelManager.h"

LevelManager* LevelManager::s_Instance = nullptr;

LevelManager::LevelManager() {

}

LevelManager::~LevelManager() {

}

void LevelManager::Init(int level) {

	if (!MapParser::GetInstance()->Load(level)) {
		std::cout << "Failed to load map" << std::endl;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("level"+std::to_string(level));

	Parser::GetInstance()->ParseTexture("Assets/textures.tml");
	Parser::GetInstance()->ParseSounds("Assets/sounds.tml");

	SoundManager::GetInstance()->PlayMusik("music"+std::to_string(level));

	Parser::GetInstance()->ParseGameObjects("Assets/level"+ std::to_string(level)+"objects.tml", &m_LevelObjects);

	//CollisionHandler::GetInstance()->SetCollisionLayer(m_LevelMap);

	Button* button1 = new Button(20, 20, nullptr, { "button_idle", "button_hover", "button_pressed" });

	m_LevelObjects.push_back(button1);

	//particleEmitter = new ParticleEmitter(DEFAULT);

	Camera::GetInstance()->SetTarget(m_LevelObjects[0]->GetOrigin()); //Player object needs to be on top of objects list for camera to follow it

}

void LevelManager::Render() {
	TextureManager::GetInstance()->Draw("bg", 0, 0, 1920, 1080, 1.0f, 1.0f, 0.5f);
	m_LevelMap->Render();
	for (int i = 0; i < m_LevelObjects.size(); i++) {
		//player->Draw();
		//enemy->Draw();
		m_LevelObjects[i]->Draw();
	}
	//particleEmitter->RenderParticles();
}

void LevelManager::Update() {
	float dt = Timer::GetInstance()->GetDeltaTime();
	m_LevelMap->Update();
	for (int i = 0; i < m_LevelObjects.size(); i++) {
		//player->Update(dt);
		//enemy->Update(dt);
		m_LevelObjects[i]->Update(dt);
	}
	//particleEmitter->UpdateParticles(dt);
	Camera::GetInstance()->Update(dt);
}

void LevelManager::SetGameMap(GameMap* gameMap) {
	if (gameMap != nullptr) {
		m_LevelMap = gameMap;
	}
	else {
		std::cout << "Unable to set map" << std::endl;
	}
}

void LevelManager::Clean() {
	SoundManager::GetInstance()->Clean();
	TextureManager::GetInstance()->Clean();
	MapParser::GetInstance()->Clean();
}