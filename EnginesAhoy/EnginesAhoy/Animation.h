#pragma once
#ifndef Animation_h
#define Animation_h
#include <string>
#include <SDL.h>

class Animation {
public:
	
	Animation() {};

	void Update(float dt);
	inline bool IsEnded() { return m_IsEnded; }
	void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SetProps(std::string textureId, int spriteRow, int spriteColumn, int frameCount, int frameOffset, int animSpeed, bool drawFrameRow);

protected:
	int m_SpriteRow, m_SpriteColumn, m_AnimSpeed, m_FrameCount, m_SpriteFrame, m_FrameOffset;
	std::string m_TextureID;
	bool m_DrawFramesRowwise = true;
	bool m_Repeat = true;
	bool m_IsEnded;
	int m_CurrentFrame;
};

#endif // !Animation_h