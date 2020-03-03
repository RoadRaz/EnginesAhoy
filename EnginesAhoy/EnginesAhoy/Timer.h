#pragma once
#ifndef Timer_h
#define Timer_h

const float TARGET_FPS = 60.0f;
const float TARGET_DELTATIME = 1.5f;

class Timer {
public:
	inline static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }
	void Tick();
	inline float GetDeltaTime() { return m_DeltaTime; }

private:
	Timer() {};
	static Timer* s_Instance;
	float m_DeltaTime;
	float m_LastTime;

};

#endif //Timer_h