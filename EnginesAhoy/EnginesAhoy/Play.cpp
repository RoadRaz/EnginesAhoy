#include "Play.h"

Play::Play() {}

bool Play::Init() {
	m_EditMode = false;
	m_Ctxt = Engine::GetInstance()->GetRenderer();

	m_LevelMap = MapParser::GetInstance()->GetMap("level1");
	Parser::GetInstance()->ParseTexture("Assets/textures.tml");

	TileLayer* collissionLayer = (TileLayer*)m_LevelMap->GetMapLayers().back();

	int tileWidth = collissionLayer->GetTileWidth();
	int tileHeight = collissionLayer->GetTileHeight();
	int width = collissionLayer->GetColCount() * tileWidth;
	int height = collissionLayer->GetRowCount() * tileHeight;

	Camera::GetInstance()->SetSceneLimit(width, height);

	CollisionHandler::GetInstance()->SetCollisionMap(collissionLayer->GetTileMap(), tileHeight, tileWidth, collissionLayer->GetRowCount(), collissionLayer->GetColCount());
	Warrior* player = new Warrior(new Properties("player",500, 200, 24, 32));
	Camera::GetInstance()->SetTarget(player->GetOrigin());
	m_GameObjects.push_back(player);

	std::cout << "play state initialized" << std::endl;
	return true;
}

void Play::Render() {
	SDL_SetRenderDrawColor(m_Ctxt, 48, 96, 130, 255);
	SDL_RenderClear(m_Ctxt);

	m_LevelMap->Render();
	for (auto gameObj : m_GameObjects) {
		gameObj->Draw();
	}

	SDL_Rect camera = Camera::GetInstance()->GetViewBox();

	if (m_EditMode) {

	}

	SDL_RenderCopy(m_Ctxt, nullptr, &camera, nullptr);
	SDL_RenderPresent(m_Ctxt);
}

void Play::Update() {
	Events();

	if (!m_EditMode) {
		float dt = Timer::GetInstance()->GetDeltaTime();

		for (auto gameObj : m_GameObjects) {
			gameObj->Update(dt);
		}

		Camera::GetInstance()->Update(dt);

		m_LevelMap->Update();
	}


}

void Play::Events() {

	if (!m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_M)) {
		OpenMenu();
	}

	if (!m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)) {
		m_EditMode = true;
		SDL_Delay(200);
	}
	if (m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_F5)) {
		m_EditMode = false;
		SDL_Delay(200);
	}
}

bool Play::Exit() {

	for (auto gameObj : m_GameObjects) {
		gameObj->Clean();
		delete gameObj;
	}

	m_GameObjects.clear();
	TextureManager::GetInstance()->Clean();

	std::cout << "Exit Play" << std::endl;
	return true;

}

void Play::OpenMenu() {
	//Engine::GetInstance()->ChangeState(new Menu());
}

void Play::PauseGame() {

}