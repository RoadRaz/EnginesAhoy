#pragma once
#ifndef SEQUENCE_ANIMATION_H
#define SEQUENCE_ANIMTAION_H
#include <SDL.h>
#include "Animation.h"
#include <map>
#include <string>
#include <vector>

struct Sequence {
	int Speed;
	int FrameCount;
	int Width, Height;
	std::vector<int> xOffsets;
	std::vector<int> yOffsets;
	std::vector<std::string> TextureIDs;
};

class SequenceAnimation : public Animation{

public:
	SequenceAnimation(bool repeat = true) : Animation(repeat) {};

	void Update(float dt);
	void Parse(std::string source);
	void SetCurrentSequence(std::string sequenceId);
	void SetRepeat(bool repeat) { m_Repeat = repeat; };
	void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SetProps(std::string textureId, int spriteRow, int spriteColumn, int frameCount, int frameOffset, int animSpeed, bool drawFramesRowwise);

private:
	Sequence m_CurrentSequence;
	std::map<std::string, Sequence> m_SequenceMap;
};
#endif