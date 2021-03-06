#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include <string>
#include "Transform.h"
#include "Engine.h"
#include "TextureManager.h"

enum ParticleType { DEFAULT = 0, YELLOW = 3 };

class Particle {
public:

	Particle(Transform tf, float vx, float vy, Uint32 lifetime, ParticleType type) {
		m_Tf = tf;
		m_xVel = vx;
		m_yVel = vy;
		m_Type = type;
		m_Tf.TextureID = tf.TextureID;
		m_LifeTime = (SDL_GetTicks() + lifetime);
		TextureManager::GetInstance()->QueryTexture(tf.TextureID, &m_Tf.Width, &m_Tf.Height);
	}

	Vector2D GetVelocity() {
		return Vector2D(m_xVel, m_yVel);
	}

	ParticleType GetType() {
		return m_Type;
	}

	virtual void Show() {
		TextureManager::GetInstance()->Draw(m_Tf.TextureID, m_Tf.X, m_Tf.Y, m_Tf.Width, m_Tf.Height);
	}

	virtual void Move(float dt) {
		m_Tf.X += m_xVel * dt;
		m_Tf.Y += m_yVel * dt;
	}

	virtual bool IsDead() {
		const SDL_Rect vp = Engine::GetInstance()->GetViewPort();
		return ((SDL_GetTicks() >= m_LifeTime) || (m_Tf.X < vp.x) || (m_Tf.Y < vp.y) || (m_Tf.X > vp.x+vp.w) || (m_Tf.Y > vp.y+vp.h));
	}

	virtual void Kill() {
		m_LifeTime = SDL_GetTicks();
	}

	Transform GetTransform() {
		return m_Tf;
	}

	void SetSegment(int x, int y) {
		segment_x = x;
		segment_y = y;
	}

	int segment_x, segment_y = 0;
private:
	ParticleType m_Type;
	Transform m_Tf;
	Uint32 m_LifeTime;
	float m_xVel, m_yVel;
};

#endif