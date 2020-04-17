#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"
#include "Vendor/tinyxml_2_6_2/tinyxml.h"

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

bool TextureManager::ParseTexture(std::string source) {
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error()) {
		std::cout << "Failed to load " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("texture")) {
			std::string id = e->Attribute("id");
			std::string src = e->Attribute("source");
			Load(id, src);
			std::cout << "Texture Parsed Successfully : " << src << std::endl;
		}
	}

	return true;

}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float scaleX, float scaleY, float scrollRatio, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { 0, 0, width, height };
	Vector2D cam = Camera::GetInstance()->GetPosition()*scrollRatio; //For background moving at different rate
	SDL_Rect dstRect = { x - cam.X, y - cam.Y, width*scaleX, height*scaleY };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::QueryTexture(std::string textureId, int* width, int* height) {
	SDL_Texture* texture = GetTexture(textureId);
	SDL_QueryTexture(texture, NULL, NULL, width, height);
}

//Rows and Columns start at 1
void TextureManager::DrawFrameRow(std::string id, int x, int y, int width, int height, float xScale, float yScale, int row, int frame, int frameOffset, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { width*(frame+frameOffset), height*(row-1), width, height };
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect dstRect = { x - cam.X, y - cam.Y, width*xScale, height*yScale };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

//Rows and Columns start at 1
void TextureManager::DrawFrameColumn(std::string id, int x, int y, int width, int height, float xScale, float yScale, int column, int frame, int frameOffset, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { width*(column-1), height*(frame+frameOffset), width, height };
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect dstRect = { x - cam.X, y - cam.Y, width*xScale, height*yScale };
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