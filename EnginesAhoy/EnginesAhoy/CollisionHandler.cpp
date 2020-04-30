#include "CollisionHandler.h"
#include "Engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
	m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().front();
	m_CollisionTileMap = m_CollisionLayer->GetTileMap();
}

void CollisionHandler::SetCollisionMap(TileMap tileMap, int tileHeight, int tileWidth, int numberOfRows, int numberOfColumns) {
	m_CollisionTileMap = tileMap;
	m_tileHeight = tileHeight;
	m_tileWidth = tileWidth;
	m_rowCount = numberOfRows;
	m_colCount = numberOfColumns;
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b) {
	bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
	return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a) {
	//int TileSize = 32;
	//int RowCount = 20;
	//int ColCount = 60;

	int leftTile = a.x / m_tileWidth;
	int rightTile = (a.x + a.w) / m_tileWidth;

	int topTile = a.y / m_tileHeight;
	int bottomTile = (a.y + a.h) / m_tileHeight;

	if (leftTile < 0) {
		leftTile = 0;
	}

	if (rightTile > m_colCount) {
		rightTile = m_colCount;
	}

	if (topTile < 0) {
		topTile = 0;
	}

	if (bottomTile > m_rowCount) {
		bottomTile = m_rowCount;
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