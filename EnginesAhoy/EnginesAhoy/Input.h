#pragma once
#ifndef Input_h
#define Input_h
#include "SDL.h"

class Input {
public:
	static Input* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
	}

	void Listen();

	bool GetKeyDown(SDL_Scancode key);

	bool GetKeyUp(SDL_Scancode key);

private:
	Input();
	void KeyUp();
	void KeyDown();

private:
	static Input* s_Instance;
	const Uint8* m_KeyStates;

};
#endif // !Input_h
