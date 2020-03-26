#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load() {
	return Parse("level1", "assets/Maps/map.tmx");
}

bool MapParser::Clean() {
	std::map<std::string, GameMap*>::iterator it;
	for (it = m_MapDict.begin(); it != m_MapDict.end(); it++) {
		it->second = nullptr;
	}
	m_MapDict.clear();
	return true;
}

bool MapParser::Parse(std::string id, std::string source){
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		std::cerr << "Failed to load " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	int rowCount, colCount, tileHeight, tileWidth;

	root->Attribute("width", &colCount);
	root->Attribute("height", &rowCount);
	root->Attribute("tilewidth", &tileWidth);
	root->Attribute("tileheight", &tileHeight);

	TilesetList tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
	}

	GameMap* gameMap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("layer")) {
			TileLayer* tileLayer = ParseTileLayer(e, tilesets, tileHeight, tileWidth, rowCount, colCount);
			gameMap->m_MapLayers.push_back(tileLayer);
		}
	}

	m_MapDict[id] = gameMap;
	return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset) {
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.FirstID);
	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;
	xmlTileset->Attribute("columns", &tileset.NumberOfColumns);
	tileset.NumberOfRows = tileset.TileCount / tileset.NumberOfRows;
	xmlTileset->Attribute("tilewidth", &tileset.TileWidth);
	xmlTileset->Attribute("tileheight", &tileset.TileHeight);

	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");
	return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileHeight, int tileWidth, int rowCount, int columnCount) {
	TiXmlElement* data = nullptr;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("data")) {
			data = e;
			break;
		}
	}

	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tileMap(rowCount, std::vector<int>(columnCount, 0));

	for (int row = 0; row < rowCount; row++) {
		for (int col = 0; col < columnCount; col++) {
			//getline(iss, id, ",");
			std::getline(iss, id, ',');
			std::stringstream convertor(id);
			convertor >> tileMap[row][col];

			if (!iss.good()) {
				break;
			}
		}
	}

	return (new TileLayer(tileHeight, tileWidth , rowCount, columnCount, tileMap, tilesets));
}