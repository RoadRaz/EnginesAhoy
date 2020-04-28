#pragma once
#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H
#include <SDL.h>
#include <string>
#include "Animation.h"

class SpriteAnimation : public Animation {

public:
	SpriteAnimation(bool repeat = true) : Animation(repeat) {};

	void Update(float dt);
	void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SetProps(std::string textureId, int spriteRow, int spriteColumn, int frameCount, int frameOffset, int animSpeed, bool drawFramesRowwise);


private:
	int m_Speed;
	int m_SpriteRow;
	int m_SpriteColumn;
	int m_FrameCount;
	std::string m_TextureID;

};

#endif