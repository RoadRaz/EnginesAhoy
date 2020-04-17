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
	std::vector<std::string> TextureIDs;
};

class SequenceAnimation : public Animation{

public:
	//SequenceAnimation(bool repeat = true);

	void Update(float dt);
	void Parse(std::string source);
	void SetCurrentSequence(std::string sequenceId);
	void SetRepeat(bool repeat) { m_Repeat = repeat; };
	void DrawFrame(float x, float y, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	Sequence m_CurrentSequence;
	std::map<std::string, Sequence> m_SequenceMap;
};
#endif