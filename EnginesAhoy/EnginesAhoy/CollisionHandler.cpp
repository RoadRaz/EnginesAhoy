#include "CollisionHandler.h"
#include "Engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
	m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().front();
	m_CollisionTileMap = m_CollisionLayer->GetTileMap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b) {
	bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
	return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a) {
	int TileSize = 32;
	int RowCount = 20;
	int ColCount = 60;

	int leftTile = a.x / TileSize;
	int rightTile = (a.x + a.w) / TileSize;

	int topTile = a.y / TileSize;
	int bottomTile = (a.y + a.h) / TileSize;

	if (leftTile < 0) {
		leftTile = 0;
	}

	if (rightTile > ColCount) {
		rightTile = ColCount;
	}

	if (topTile < 0) {
		topTile = 0;
	}

	if (bottomTile > RowCount) {
		bottomTile = RowCount;
	}

	for (int i = leftTile; i <= rightTile; ++i){
		for (int j = topTile; j <= bottomTile; ++j) {
			if (m_CollisionTileMap[j][i] > 0) {
				return true;
			}
		}
	}
	return false;
}