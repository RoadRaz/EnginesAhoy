#pragma once
#ifndef Warrior_h
#define Warrior_h
#include "Character.h"

class Warrior : public Character {
public:
	Warrior(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	int m_Row, m_Frame, m_FrameCount, m_Column, m_AnimSpeed;

};
#endif // !Warrior_h
