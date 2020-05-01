#pragma once
#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H
#define DEFAULT_PARTICLE_COUNT 500
#include "Particle.h"
#include "RandomUtil.h"

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
				m_ParticleTextureIDs = { "particle1", "particle2", "particle3", "particle4"};
				m_ParticleCount = DEFAULT_PARTICLE_COUNT;
				break;
			case YELLOW:
				m_ParticleTextureIDs = { "particle1", "particle2", "particle3", "particle4" };
				m_ParticleCount = DEFAULT_PARTICLE_COUNT;
				break;
			default:
				m_ParticleTextureIDs = { "particle1", "particle2", "particle3", "particle4" };
				m_ParticleCount = DEFAULT_PARTICLE_COUNT;
				break;
		}

		for (int i = 0; i < m_ParticleCount; i++) {
			m_Particles.push_back(NewParticle());
		}
	}

	void MoveAndSegmet(int part, float dt, SDL_Rect vp) {
		if (!checkCollisions) {
			m_Particles[part]->Move(dt);
			return;
		}
		int old_seg_x = (m_Particles[part]->GetTransform().X - vp.x) / 128;
		int old_seg_y = (m_Particles[part]->GetTransform().Y - vp.y) / 72;

		m_Particles[part]->Move(dt);

		int new_seg_x = (m_Particles[part]->GetTransform().X - vp.x) / 128;
		int new_seg_y = (m_Particles[part]->GetTransform().Y - vp.y) / 72;

		if (old_seg_x < 0 || old_seg_y < 0) {
			return;
		}

		if (new_seg_x > 9 || new_seg_y > 9) {
			return;
		}

		if (new_seg_x != old_seg_x || new_seg_y != old_seg_y) {
			RemoveFromSegment(part, old_seg_x, old_seg_y);
			if (new_seg_x < 10 && new_seg_y < 10) {
				segment[new_seg_x][new_seg_y].push_back(part);
				m_Particles[part]->SetSegment(new_seg_x, new_seg_y);
				//std::cout << segment[new_seg_x][new_seg_y].size() << std::endl;
			}
		}
	}

	void RemoveFromSegment(int part, int x, int y) {
		if (!checkCollisions) {
			return;
		}
		auto it = std::find(segment[x][y].begin(), segment[x][y].end(), part);
		if (it != segment[x][y].end()) {
			segment[x][y].erase(it);
			//std::cout << segment[old_seg_x][old_seg_y].size() << std::endl;
		}
	}

	Particle* CheckAndResolveCollision(int part) {
		if (!checkCollisions) {
			return nullptr;
		}
		std::vector<int> partList = segment[m_Particles[part]->segment_x][m_Particles[part]->segment_y];
		for (int i = 0; i < partList.size(); i++) {
			int part2 = partList[i];
			if (m_Particles[part2]->GetType() == YELLOW) {
				continue;
			}
			if (part != part2) {
				float xDiff = std::abs(m_Particles[part]->GetTransform().X - m_Particles[part2]->GetTransform().X);
				float yDiff = std::abs(m_Particles[part]->GetTransform().Y - m_Particles[part2]->GetTransform().Y);

				if (xDiff < 10 && yDiff < 10) {

					float newX = std::abs(m_Particles[part]->GetTransform().X + m_Particles[part2]->GetTransform().X) / 2;
					float newY = std::abs(m_Particles[part]->GetTransform().Y + m_Particles[part2]->GetTransform().Y) / 2;

					float vxDiff = (m_Particles[part]->GetVelocity().X + m_Particles[part2]->GetVelocity().X) / 2;
					float vyDiff = (m_Particles[part]->GetVelocity().Y + m_Particles[part2]->GetVelocity().Y) / 2;

					m_Particles[part]->Kill();
					m_Particles[part2]->Kill();

					return YellowParticle(newX, newY, vxDiff, vyDiff);
				}
			}
		}
		return nullptr;
	}

	void UpdateParticles(float dt) {
		const SDL_Rect vp = Engine::GetInstance()->GetViewPort();
		for (int i = 0; i < m_Particles.size(); i++) {
			if (m_Particles[i]->IsDead()) {
				RemoveFromSegment(i, m_Particles[i]->segment_x, m_Particles[i]->segment_y);
				delete m_Particles[i];
				m_Particles[i] = NewParticle();
			}
			else {
				//m_Particles[i]->Move(dt);
				MoveAndSegmet(i, dt, vp);
			}
			if (m_Particles[i]->GetType() != YELLOW) {
				Particle* newPart = CheckAndResolveCollision(i);
				if (newPart != nullptr) {

					RemoveFromSegment(i, m_Particles[i]->segment_x, m_Particles[i]->segment_y);
					delete m_Particles[i];
					m_Particles[i] = newPart;
				}
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
		int index = RandomUtil::RandI(0, m_ParticleTextureIDs.size()-1);
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
		return new Particle(Transform(x, 0, 0, 0, textureId), vx, vy, lifetime, DEFAULT);
	}

	Particle* YellowParticle(float x, float y, float vx, float vy) {
		SDL_Rect vp = Engine::GetInstance()->GetViewPort();
		//float x = RandomUtil::RandI(vp.x + x, vp.x + vp.w);
		//float vx = RandomUtil::RandI(1, 2);
		//float vy = RandomUtil::RandI(5, 10);
		Uint32 lifetime = RandomUtil::RandI(8000, 20000);
		return new Particle(Transform(x, y, 0, 0, m_ParticleTextureIDs[YELLOW]), vx, vy, lifetime, YELLOW);
	}

private:
	ParticleType m_CurrentParticleType;
	Uint32 m_ParticleCount;
	std::vector<Particle*> m_Particles;
	std::vector<std::string> m_ParticleTextureIDs;
	std::vector<int> segment[10][10];

	bool checkCollisions = true;
};

#endif