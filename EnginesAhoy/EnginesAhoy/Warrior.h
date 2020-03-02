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

};
#endif // !Warrior_h
