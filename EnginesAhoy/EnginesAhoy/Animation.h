#pragma once
#ifndef Animation_h
#define Animation_h
#include <string>
#include <SDL.h>

class Animation {
public:
	Animation() {};

	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight);
	void SetProps(std::string textureId, int spriteRow, int spriteColumn, int frameCount, int frameOffset, int animSpeed, bool drawFrameRow, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	int m_SpriteRow, m_SpriteColumn, m_AnimSpeed, m_FrameCount, m_SpriteFrame, m_FrameOffset;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;
	bool m_DrawFramesRowwise = true;

};

#endif // !Animation_h