#pragma once
#ifndef Character_h
#define Character_h
#include "GameObject.h"
#include <map>
#include <string>
#include "Animation.h"
#include "SpriteAnimation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "CollisionHandler.h"

class Character : public GameObject {
public:
	Character(Properties* props) : GameObject(props) {}

	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

	inline RigidBody* GetRigidBody() {
		return m_RigidBody;
	}

	inline void AddAnimation(std::string key, Animation* animation) {
		m_AnimationMap[key] = animation;
	}

	inline Animation* GetAnimation(std::string key) {
		return m_AnimationMap[key];
	}

	inline void SetAnimation(Animation* animation) {
		m_Animation = animation;
	}

	inline void SetAnimation(std::string key) {
		m_Animation = m_AnimationMap[key];
	}

protected:
	RigidBody* m_RigidBody;
	Animation* m_Animation;
	std::string m_Name;
	std::map<std::string, Animation*> m_AnimationMap;
	Collider* m_Collider;
};
#endif // !Character_h
