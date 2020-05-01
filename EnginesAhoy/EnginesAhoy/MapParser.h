#pragma once
#ifndef MapParser_h
#define MapParser_h
#include "Vendor/tinyxml_2_6_2/tinyxml.h"
#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"

class MapParser {
public:
	bool Load(int level);
	bool Clean();

	inline GameMap* GetMap(std::string id) { return m_MapDict[id]; }
	inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

private:
	MapParser() {}
	static MapParser* s_Instance;
	std::map<std::string, GameMap*> m_MapDict;

private:
	bool Parse(std::string id, std::string source);
	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileHeight, int tileWidth, int rowCount, int columnCount);
};

#endif //MapParser_h