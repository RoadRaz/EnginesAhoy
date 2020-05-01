#pragma once
#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H
#include "Timer.h"
#include "Input.h"
#include "Camera.h"
#include "Parser.h"
#include "MapParser.h"
#include "TileLayer.h"
#include "ObjectFactory.h"
#include "TextureManager.h"
#include "CollisionHandler.h"
#include "SoundManager.h"
#include "RandomUtil.h"
#include "Button.h"
#include "ParticleEmitter.h"

class LevelManager {
public:
	virtual ~LevelManager();

	void Init(int level);
	void Clean();
	void Render();
	void Update();

	void SetGameMap(GameMap* tileMap);

	inline static LevelManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new LevelManager(); }

private:
	static LevelManager* s_Instance;
	GameObject* player;
	std::string bg;
	GameMap* m_LevelMap;
	std::vector<GameObject*> m_LevelObjects;
	LevelManager();
};
#endif