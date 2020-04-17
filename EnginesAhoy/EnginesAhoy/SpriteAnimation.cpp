#include "SpriteAnimation.h"
#include "TextureManager.h"

//SpriteAnimation::SpriteAnimation(bool repeat):Animation(repeat) {}

void SpriteAnimation::Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip) {
	if (m_DrawFramesRowwise) {
		TextureManager::GetInstance()->DrawFrameRow(m_TextureID, x, y, spriteWidth, spriteHeight, xScale, yScale, m_SpriteRow, m_CurrentFrame, m_FrameOffset, flip);
	}
	else {
		TextureManager::GetInstance()->DrawFrameColumn(m_TextureID, x, y, spriteWidth, spriteHeight, xScale, yScale, m_SpriteColumn, m_CurrentFrame, m_FrameOffset, flip);
	}
}

void SpriteAnimation::Update(float dt) {
	m_CurrentFrame = (SDL_GetTicks() / m_Speed) % m_FrameCount;
}

void SpriteAnimation::SetProps(std::string textureId, int spriteRow, int spriteColumn, int frameCount, int frameOffset, int animSpeed, bool drawFramesRowwise) {
	m_TextureID = textureId;
	m_SpriteRow = spriteRow;
	m_SpriteColumn = spriteColumn;
	m_FrameCount = frameCount;
	m_FrameOffset = frameOffset;
	m_Speed = animSpeed;
	m_DrawFramesRowwise = drawFramesRowwise;
}
