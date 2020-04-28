#include "Animation.h"
#include "TextureManager.h"

//void Animation::Update(float dt) {
//	m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
//}
//
//void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip) {
//	if (m_DrawFramesRowwise) {
//		TextureManager::GetInstance()->DrawFrameRow(m_TextureID, x, y, spriteWidth, spriteHeight, xScale, yScale, m_SpriteRow, m_SpriteFrame, m_FrameOffset, flip);
//	}
//	else {
//		TextureManager::GetInstance()->DrawFrameColumn(m_TextureID, x, y, spriteWidth, spriteHeight,xScale, yScale, m_SpriteColumn, m_SpriteFrame, m_FrameOffset, flip);
//	}
//}
//
//void Animation::SetProps(std::string textureId, int spriteRow, int spriteColumn, int frameCount, int frameOffset, int animSpeed, bool drawFramesRowwise) {
//	m_TextureID = textureId;
//	m_SpriteRow = spriteRow;
//	m_SpriteColumn = spriteColumn;
//	m_FrameCount = frameCount;
//	m_FrameOffset = frameOffset;
//	m_AnimSpeed = animSpeed;
//	m_DrawFramesRowwise = drawFramesRowwise;
//}