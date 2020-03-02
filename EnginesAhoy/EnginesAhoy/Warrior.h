#pragma once
#ifndef Warrior_h
#define Warrior_h
#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include <map>

class Warrior : public Character {
public:
	Warrior(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();
	virtual RigidBody* GetRigidBody();
	virtual Animation* GetAnimation(std::string key);
	virtual void SetAnimation(Animation* animation);
	virtual void SetAnimation(std::string key);
	virtual void AddAnimation(std::string key, Animation* animation);

private:
	Animation* m_Animation;
	RigidBody* m_RigidBody;
	std::map<std::string, Animation*> m_AnimationMap;
};
#endif // !Warrior_h
