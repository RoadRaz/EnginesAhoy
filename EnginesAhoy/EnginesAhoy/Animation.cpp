#include "Animation.h"
#include "TextureManager.h"

void Animation::Update() {
	m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight) {
	if (m_DrawFramesRowwise) {
		TextureManager::GetInstance()->DrawFrameRow(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_FrameOffset, m_Flip);
	}
	else {
		TextureManager::GetInstance()->DrawFrameColumn(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteColumn, m_SpriteFrame, m_FrameOffset, m_Flip);
	}
}

void Animation::SetProps(std::string textureId, int spriteRow, int spriteColumn, int frameCount, int frameOffset, int animSpeed, bool drawFramesRowwise, SDL_RendererFlip flip) {
	m_TextureID = textureId;
	m_SpriteRow = spriteRow;
	m_SpriteColumn = spriteColumn;
	m_FrameCount = frameCount;
	m_FrameOffset = frameOffset;
	m_AnimSpeed = animSpeed;
	m_DrawFramesRowwise = drawFramesRowwise;
	m_Flip = flip;

}