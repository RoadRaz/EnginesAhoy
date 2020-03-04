#include "TileLayer.h"

TileLayer::TileLayer(int tileHeight, int tileWidth, int numberOfRows, int numberOfColumns, TileMap tileMap, TilesetList tilesetList){
	m_TileHeight = tileHeight;
	m_TileWidth = tileWidth;
	m_NumberOfRows = numberOfRows;
	m_NumberOfColumns = numberOfColumns;
	m_Tilemap = tileMap;
	m_TileSets = tilesetList;
}

void TileLayer::Render() {

}

void TileLayer::Update() {

}