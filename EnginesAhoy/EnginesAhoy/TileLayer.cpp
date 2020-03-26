#include "TileLayer.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tileHeight, int tileWidth, int numberOfRows, int numberOfColumns, TileMap tileMap, TilesetList tilesetList): m_TileSets(tilesetList), m_NumberOfColumns(numberOfColumns), m_NumberOfRows(numberOfRows),m_Tilemap(tileMap){
	//m_TileHeight = tileHeight;
	//m_TileWidth = tileWidth;
	//m_NumberOfRows = numberOfRows;
	//m_NumberOfColumns = numberOfColumns;
	//m_Tilemap = tileMap;

	for (unsigned int i = 0; i < m_TileSets.size(); i++) {
		TextureManager::GetInstance()->Load(m_TileSets[i].Name, "assets/maps/" + m_TileSets[i].Source);
	}
}

void TileLayer::Render() {
	for (unsigned int i = 0; i < m_NumberOfRows; i++){
		for (unsigned int j = 0; j < m_NumberOfColumns; j++) {
			int tileID = m_Tilemap[i][j];

			if (tileID == 0) {
				continue;
			}
			else {
				int index = 0;
				if (m_TileSets.size() > 1) {
					for (unsigned int k = 1; k < m_TileSets.size(); k++) {
						if (tileID > m_TileSets[k].FirstID&& tileID < m_TileSets[k].LastID) {
							tileID = tileID + m_TileSets[k].TileCount - m_TileSets[k].LastID;
							index = k;
							break;
						}
					}
				}
				Tileset ts = m_TileSets[index];
				int tileRow = tileID / ts.NumberOfColumns;
				int tileColumn = tileID - tileRow * ts.NumberOfColumns - 1;

				if (tileID % ts.NumberOfColumns == 0) {
					tileRow--;
					tileColumn = ts.NumberOfColumns - 1;
				}

				TextureManager::GetInstance()->DrawTile(ts.Name, j*ts.TileWidth, i*ts.TileWidth, ts.TileWidth, ts.TileHeight, tileRow, tileColumn, SDL_FLIP_NONE);
			}
		}
	}
}

void TileLayer::Update() {

}