#pragma once
#ifndef CollisionHandler_h
#define CollisionHandler_h
#include "SDL.h"
#include <vector>
#include "TileLayer.h"
#include "GameMap.h"
#include "Engine.h"

class CollisionHandler {
public:
	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool MapCollision(SDL_Rect a);

	inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }

private:
	static CollisionHandler* s_Instance;
	CollisionHandler();
	TileMap m_CollisionTileMap;
	TileLayer* m_CollisionLayer;

};

#endif