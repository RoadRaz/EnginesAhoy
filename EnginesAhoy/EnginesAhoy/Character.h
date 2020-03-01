#pragma once
#ifndef Character_h
#define Character_h
#include "GameObject.h"
#include "SDL.h"

class Character : public GameObject {
public:
	Character(Properties* props) : GameObject(props) {}

	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

protected:
	std::string m_Name;
};
#endif // !Character_h
