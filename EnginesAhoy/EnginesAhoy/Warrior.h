#pragma once
#ifndef Warrior_h
#define Warrior_h
#include "Character.h"
#define JUMP_TIME 15.0f;
#define JUMP_FORCE 10.0f;
#define RUN_FORCE 4.0f;
#define ATTACK_TIME 20.0f;

class Warrior : public Character {
public:
	Warrior(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	bool m_IsJumping;
	bool m_IsGrounded;
	bool m_IsFalling;
	bool m_IsAttacking;
	bool m_IsCrouching;
	bool m_IsRunning;

	float m_JumpTime;
	float m_JumpForce;
	float m_AttackTime;

	float m_RunForce;

	Vector2D m_LastSafePostion;

};
#endif // !Warrior_h
