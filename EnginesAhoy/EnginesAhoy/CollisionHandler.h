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

	void SetCollisionMap(TileMap tileMap, int tileHeight, int tileWidth, int numberOfRows, int numberOfColumns);

	inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }

private:
	int m_tileHeight = 32;
	int m_tileWidth = 32;
	int m_rowCount = 20;
	int m_colCount = 60;
	static CollisionHandler* s_Instance;
	CollisionHandler();
	TileMap m_CollisionTileMap;
	TileLayer* m_CollisionLayer;

};

#endif