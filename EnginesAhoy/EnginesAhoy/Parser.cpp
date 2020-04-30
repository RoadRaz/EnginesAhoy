#include "Parser.h"
#include "Transform.h"
#include "TextureManager.h"
#include "SoundManager.h"

Parser* Parser::s_Instance = nullptr;

Parser::Parser() {

}

bool Parser::ParseSounds(std::string source) {

	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		std::cout << "Failed to load sounds file" << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {

		if (e->Value() == std::string("effect")) {
			SoundManager::GetInstance()->LoadEffect(e->Attribute("id"), e->Attribute("source"));
			continue;
		}
		if (e->Value() == std::string("music")) {
			SoundManager::GetInstance()->LoadMusik(e->Attribute("id"), e->Attribute("source"));
			continue;
		}
	}
	std::cout << "Parsed music files" << std::endl;
	return true;
}

void Parser::ParseGameObjects(std::string source, std::vector<GameObject*>* target) {

	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		std::cout << "Failed to load gameobjects file" << std::endl;
		return;
	}

	TiXmlElement* root = xml.RootElement();

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("object")) {
			int x, y, width, height, flip = 0;
			double scX, scY = 0;
			const char* objType;
			const char* texID;
			double sratio = 0;
			double rot = 0;
			int category = -1;

			objType = e->Attribute("type");
			texID = e->Attribute("texture");

			e->Attribute("x", &x);
			e->Attribute("y", &y);
			e->Attribute("w", &width);
			e->Attribute("h", &height);
			e->Attribute("flip", &flip);
			e->Attribute("category", &category);

			SDL_RendererFlip rflip;
			if (flip == 0) { rflip = SDL_FLIP_NONE; }
			if (flip == 1) { rflip = SDL_FLIP_HORIZONTAL; }
			if (flip == 2) { rflip = SDL_FLIP_VERTICAL; }

			e->Attribute("sX", &scX);
			e->Attribute("sY", &scY);
			e->Attribute("sratio", &sratio);

			//Properties* props = new Properties(texID, x, y, width, height, rflip, scX, scY, rot, sratio);
			Properties* props = new Properties(texID, x, y, width, height, rflip);
			auto object = ObjectFactory::GetInstance()->CreateObject(objType, props);

			if (object) {
				target->push_back(std::move(object));
			}
		}
		std::cout << "Parsed" << std::endl;
	}
}

bool Parser::ParseTexture(std::string source) {
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
			TextureManager::GetInstance()->Load(id, src);
			std::cout << "Texture Parsed Successfully : " << src << std::endl;
		}
	}

	return true;
}

//TileMap* Parser::ParseMap(std::string source) {
//}

//TileSet Parser::ParseTileSet(TiXmlElement* xmlTileSet) {
//
//}

TileLayer* Parser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileHeight, int tileWidth, int rowCount, int columnCount) {
}