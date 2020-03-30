#pragma once
#ifndef Warrior_h
#define Warrior_h
#include "Character.h"
#define JUMP_TIME 15.0f;
#define JUMP_FORCE 10.0f;

class Warrior : public Character {
public:
	Warrior(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	bool m_IsJumping;
	bool m_IsGrounded;

	float m_JumpTime;
	float m_JumpForce;

	Vector2D m_LastSafePostion;

};
#endif // !Warrior_h
