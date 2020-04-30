#pragma once
#ifndef PARSER_H
#define PARSER_H
#include "ObjectFactory.h"
#include "Vendor/tinyxml_2_6_2/tinyxml.h"
#include "TileLayer.h"

class Parser {
public:
	static inline Parser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Parser(); }
	void ParseGameObjects(std::string source, std::vector<GameObject*>* target);

	bool ParseTexture(std::string source);

	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileHeight, int tileWidth, int rowCount, int columnCount);

private:
	Parser();
	static Parser* s_Instance;
};
#endif