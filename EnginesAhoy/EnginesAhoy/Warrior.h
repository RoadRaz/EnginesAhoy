#pragma once
#ifndef Warrior_h
#define Warrior_h
#include "Character.h"
#include "Animation.h"

class Warrior : public Character {
public:
	Warrior(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	Animation* m_Animation;
};
#endif // !Warrior_h
