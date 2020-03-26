#pragma once
#ifndef TileLayer_h
#define TileLayer_h
#include "Layer.h"
#include <string>
#include <vector>

struct Tileset {
	int FirstID, LastID;
	int NumberOfRows, NumberOfColumns;
	int TileCount, TileHeight, TileWidth;
	std::string Name, Source;
};

using TilesetList = std::vector<Tileset> ;
using TileMap = std::vector<std::vector<int> >;

class TileLayer : public Layer {
public :
	TileLayer(int tileHeight, int tileWidth, int numberOfRows, int numberOfColumns, TileMap tileMap, TilesetList tilesetList);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTileMap() {
		return m_Tilemap;
	}

private:
	int m_TileHeight, m_TileWidth;
	int m_NumberOfRows, m_NumberOfColumns;
	TileMap m_Tilemap;
	TilesetList m_TileSets;

};
#endif