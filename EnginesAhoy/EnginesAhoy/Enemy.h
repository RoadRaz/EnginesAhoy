#pragma once
#ifndef Enemy_h
#define Enemy_h
#include "Character.h"

class Enemy : public Character {
public:
	Enemy(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	Vector2D m_LastSafePostion;

};
#endif // Enemy_h
