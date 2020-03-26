#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename) {
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr) {
		SDL_Log("Failed to load surface : %s , %s", filename.c_str(),SDL_GetError());
		return false;
	}

	SDL_Log("Loaded surface : %s ", filename.c_str());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(),surface);
	if (texture == nullptr) {
		SDL_Log("Failed to create texture from surface : %s , %s", filename.c_str(), SDL_GetError());
		return false;
	}

	SDL_Log("Created Texture from surface : %s", filename.c_str());

	m_TextureMap[id] = texture;
	return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { 0, 0, width, height };
	Vector2D cam = Camera::GetInstance()->GetPosition()*0.5; //For background moving at different rate
	SDL_Rect dstRect = { x - cam.X, y - cam.Y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

//Rows and Columns start at 1
void TextureManager::DrawFrameRow(std::string id, int x, int y, int width, int height, int row, int frame, int frameOffset, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { width*(frame+frameOffset), height*(row-1), width, height };
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect dstRect = { x - cam.X, y - cam.Y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

//Rows and Columns start at 1
void TextureManager::DrawFrameColumn(std::string id, int x, int y, int width, int height, int column, int frame, int frameOffset, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { width*(column-1), height*(frame+frameOffset), width, height };
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect dstRect = { x - cam.X, y - cam.Y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

//Rows and Columns start at 1
void TextureManager::DrawTile(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { width * frame, height * (row-1), width, height };
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect dstRect = { x - cam.X, y - cam.Y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Drop(std::string id) {
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);
}

void TextureManager::Clean() {
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++) {
		SDL_DestroyTexture(it->second);
	}
	m_TextureMap.clear();

	SDL_Log("Texture Map Cleaned!");
}