#pragma once
#ifndef TextureManager_h
#define TextureManager_h
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_image.h"

class TextureManager {
public:
	static TextureManager* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); 
	}

	bool Load(std::string id, std::string filename);
	bool ParseTexture(std::string source);
	void QueryTexture(std::string textureId, int* width, int* height);
	inline SDL_Texture* GetTexture(std::string textureId) { return m_TextureMap[textureId]; };
	void Drop(std::string id);
	void Clean();
	
	void Draw(std::string id, int x, int y, int width, int height, float scaleX = 1.0f, float scaleY = 1.0f, float scrollRatio = 1.0f, SDL_RendererFlip flip=SDL_FLIP_NONE);
	void DrawFrameRow(std::string id, int x, int y, int width, int height, float xScale, float yScale, int row, int frame, int frameOffset, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrameColumn(std::string id, int x, int y, int width, int height, float xScale, float yScale, int column, int frame, int frameOffset, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawTile(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	TextureManager() {};
	std::map<std::string, SDL_Texture*> m_TextureMap;
	static TextureManager* s_Instance;
};
#endif // !TextureManager_h
