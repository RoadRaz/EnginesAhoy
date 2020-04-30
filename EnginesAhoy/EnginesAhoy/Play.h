#pragma once
#ifndef PLAY_H
#define PLAY_H
#include <iostream>
#include "GameMap.h"
#include "GameObject.h"
#include "GameState.h"
#include "Enemy.h"
#include "Warrior.h"
#include "Timer.h"
#include "Menu.h"
#include "Input.h"
#include "Camera.h"
#include "MapParser.h"
#include "TileLayer.h"
#include "ObjectFactory.h"
#include "TextureManager.h"
#include "CollisionHandler.h"
#include "Parser.h"

class Play : public GameState{
public:
	Play();
	void Events();
	virtual bool Init();
	virtual bool Exit();
	virtual void Update();
	virtual void Render();

private:
	static void OpenMenu();
	static void PauseGame();

private:
	bool m_EditMode;
	GameMap* m_LevelMap;
	std::vector<GameObject*> m_GameObjects;
};

#endif