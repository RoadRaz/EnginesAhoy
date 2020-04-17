#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include <string>
#include "Transform.h"
#include "Engine.h"
#include "TextureManager.h"

class Particle {
public:

	Particle(Transform tf, float vx, float vy, Uint32 lifetime) {
		m_xVel = vx;
		m_yVel = vy;
		m_Tf.TextureID = tf.TextureID;
		m_LifeTime = (SDL_GetTicks() + lifetime);
		TextureManager::GetInstance()->QueryTexture(tf.TextureID, &m_Tf.Width, &m_Tf.Height);
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
		return ((SDL_GetTicks() >= m_LifeTime) || (m_Tf.X < 0) || (m_Tf.Y < 0) || (m_Tf.X > vp.w) || (m_Tf.Y > vp.h));
	}

private:
	Transform m_Tf;
	Uint32 m_LifeTime;
	float m_xVel, m_yVel;
};

#endif