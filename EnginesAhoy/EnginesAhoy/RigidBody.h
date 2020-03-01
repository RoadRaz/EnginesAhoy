#pragma once
#ifndef RigidBody_h
#define RigidBody_h
#include "Vector2D.h"

#define UNIT_MASS 1.0f
#define GRAVITY 9.8f

class RigidBody {
public:
	RigidBody() {
		m_Mass = UNIT_MASS;
		m_Gravity = GRAVITY;
	};
	//Mass
	inline void SetMass(float mass) {
		m_Mass = mass;
	}
	//Gravity
	inline void SetGravity(float gravity) {
		m_Gravity = gravity;
	}
	//Force
	inline void ApplyForce(Vector2D force) {
		m_Force = force;
	}

	inline void ApplyForceX(float forceX) {
		m_Force.X = forceX;
	}

	inline void ApplyForceY(float forceY) {
		m_Force.Y = forceY;
	}

	inline void UnsetForce() {
		m_Force = Vector2D(0,0);
	}
	//Friction
	inline void ApplyFriction(Vector2D friction) {
		m_Friction = friction;
	}

	inline void UnsetFriction() {
		m_Friction = Vector2D(0, 0);
	}

	inline float GetMass() {
		return m_Mass;
	}

	inline Vector2D GetPosition() {
		return m_Position;
	}

	inline Vector2D GetAcceleration() {
		return m_Acceleration;
	}

	inline Vector2D GetVelocity() {
		return m_Velocity;
	}

	void Update(float dt) {
		m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
		m_Acceleration.Y = m_Gravity + m_Force.Y/m_Mass;
		m_Velocity = m_Acceleration * dt;
		m_Position = m_Velocity * dt;
	}

private:
	float m_Mass, m_Gravity;
	Vector2D m_Force, m_Friction;
	Vector2D m_Position, m_Velocity, m_Acceleration;

};
#endif // !RigidBody_h
