#include "Warrior.h"
#include "TextureManager.h"

Warrior::Warrior(Properties* props) : Character(props) {
	m_Column = 17;
	m_FrameCount = 3;
	m_Row = 0;
	m_AnimSpeed = 300;
}

void Warrior::Draw() {
	TextureManager::GetInstance()->DrawFrameColumn(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Column, m_Frame, m_Flip);
}

void Warrior::Update(float dt) {
	m_Frame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Warrior::Clean() {
	TextureManager::GetInstance()->Drop(m_TextureID);
}