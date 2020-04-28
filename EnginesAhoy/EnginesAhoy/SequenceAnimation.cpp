#include "SequenceAnimation.h"
#include "Vendor/tinyxml_2_6_2/tinyxml.h"
#include "TextureManager.h"
#include <iostream>

//SequenceAnimation::SequenceAnimation(bool repeat) :Animation(repeat) {}

void SequenceAnimation::Draw(float x, float y, int spriteWidth = 0 , int spriteHeight = 0,  float xScale, float yScale, SDL_RendererFlip flip) {
	TextureManager::GetInstance()->DrawSequenceFrame(m_CurrentSequence.TextureIDs[m_CurrentFrame], x, y, m_CurrentSequence.Width, m_CurrentSequence.Height, xScale, yScale,m_CurrentSequence.xOffsets[m_CurrentFrame], m_CurrentSequence.yOffsets[m_CurrentFrame], flip);
}

void SequenceAnimation::SetProps(std::string textureId, int spriteRow, int spriteColumn, int frameCount, int frameOffset, int animSpeed, bool drawFramesRowwise) {
}


void SequenceAnimation::Update(float dt) {
	if (m_Repeat || m_IsEnded) {
		m_IsEnded = false;
		m_CurrentFrame = (SDL_GetTicks() / m_CurrentSequence.Speed) % m_CurrentSequence.FrameCount;
	}

	if (!m_Repeat && m_CurrentFrame == (m_CurrentSequence.FrameCount - 1)) {
		m_IsEnded = true;
		m_CurrentFrame = (m_CurrentSequence.FrameCount - 1);
	}
}

void SequenceAnimation::SetCurrentSequence(std::string sequenceID) {
	if(m_SequenceMap.count(sequenceID) > 0){
		m_CurrentSequence = m_SequenceMap[sequenceID];
	}
	else {
		std::cout << "The given sequence animation does not match: " << sequenceID << std::endl;
	}
}

void SequenceAnimation::Parse(std::string source) {
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error()) {
		std::cout << "Failed to load Animation file: " << source << std::endl;
	}

	TiXmlElement* root = xml.RootElement();

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("sequence")) {
			Sequence seq;
			std::string seqId = e->Attribute("id");
			e->Attribute("speed", &seq.Speed);
			e->Attribute("width", &seq.Width);
			e->Attribute("height", &seq.Height);
			e->Attribute("frameCount", &seq.FrameCount);

			for (TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement()) {
				seq.TextureIDs.push_back(frame->Attribute("textureID"));
				
				int xOffset = 0;
				frame->Attribute("xOffset", &xOffset);
				seq.xOffsets.push_back(xOffset);

				int yOffset = 0;
				frame->Attribute("yOffset", &yOffset);
				seq.yOffsets.push_back(yOffset);
			}
			m_SequenceMap[seqId] = seq;
		}
	}
}