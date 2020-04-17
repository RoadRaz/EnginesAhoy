#include "SequenceAnimation.h"
#include "Vendor/tinyxml_2_6_2/tinyxml.h"
#include "TextureManager.h"
#include <iostream>

//SequenceAnimation::SequenceAnimation(bool repeat) :Animation(repeat) {}

void SequenceAnimation::DrawFrame(float x, float y, float xScale, float yScale, SDL_RendererFlip flip) {
	TextureManager::GetInstance()->Draw(m_CurrentSequence.TextureIDs[m_CurrentFrame], x, y, m_CurrentSequence.Width, m_CurrentSequence.Height, xScale, yScale, flip);
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
			}
			m_SequenceMap[seqId] = seq;
		}
	}
}