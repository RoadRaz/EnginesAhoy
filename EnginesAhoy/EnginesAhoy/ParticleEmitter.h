#pragma once
#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H
#define DEFAULT_PARTICLE_COUNT 400
#include "Particle.h"
#include "RandomUtil.h"

enum ParticleType {DEFAULT=0};

class ParticleEmitter {
public:
	ParticleEmitter(ParticleType type = DEFAULT) {
		InitParticles(DEFAULT);
	}

	~ParticleEmitter() {
		for (auto particle : m_Particles) {
			delete particle;
		}
		m_Particles.clear();
	}

	void InitParticles(ParticleType type = DEFAULT) {
		m_CurrentParticleType = type;
		m_Particles.clear();
		m_ParticleTextureIDs.clear();

		switch (m_CurrentParticleType) {
			case DEFAULT:
				m_ParticleTextureIDs = { "particle1", "particle2", "particle3" };
				m_ParticleCount = DEFAULT_PARTICLE_COUNT;
				break;
			default:
				m_ParticleTextureIDs = { "particle1", "particle2", "particle3" };
				m_ParticleCount = DEFAULT_PARTICLE_COUNT;
				break;
		}

		for (int i = 0; i < m_ParticleCount; i++) {
			m_Particles.push_back(NewParticle());
		}
	}

	void UpdateParticles(float dt) {
		for (int i = 0; i < m_Particles.size(); i++) {
			if (m_Particles[i]->IsDead()) {
				delete m_Particles[i];
				m_Particles[i] = NewParticle();
			}
			else {
				m_Particles[i]->Move(dt);
			}
		}
	}

	void RenderParticles() {
		for (auto particle : m_Particles) {
			particle->Show();
		}
	}

private:
	Particle* NewParticle() {
		int index = RandomUtil::RandI(0, m_ParticleTextureIDs.size());
		switch (m_CurrentParticleType) {
			case DEFAULT:
				return DefaultParticle(m_ParticleTextureIDs[index]);
				break;
			default:
				return DefaultParticle(m_ParticleTextureIDs[index]);
				break;
		}
	}

	Particle* DefaultParticle(std::string textureId) {
		SDL_Rect vp = Engine::GetInstance()->GetViewPort();
		float x = RandomUtil::RandI(vp.x, vp.x+vp.w);
		float vx = RandomUtil::RandI(1, 2);
		float vy = RandomUtil::RandI(5, 10);
		Uint32 lifetime = RandomUtil::RandI(8000, 20000);
		return new Particle(Transform(x, 0, 0, 0, textureId), vx, vy, lifetime);
	}

private:
	ParticleType m_CurrentParticleType;
	Uint32 m_ParticleCount;
	std::vector<Particle*> m_Particles;
	std::vector<std::string> m_ParticleTextureIDs;
};

#endif