#pragma once
#ifndef Input_h
#define Input_h
#include "SDL.h"
#include "Vector2D.h"

class Input {
public:
	static Input* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
	}

	void Listen();

	bool GetKeyDown(SDL_Scancode key);

	bool GetKeyUp(SDL_Scancode key);

	Vector2D GetMousePosition();

	bool GetMouseButtonDownLeft();
	bool GetMouseButtonDownRight();

	bool GetMouseButtonUpLeft();
	bool GetMouseButtonUpRight();

private:
	Input();
	void KeyUp();
	void KeyDown();

private:
	static Input* s_Instance;
	const Uint8* m_KeyStates;
	bool mouseLeftButtonUp = true;
	bool mouseLeftButtonDown = false;
	bool mouseRightButtonUp = true;
	bool mouseRightButtonDown = false;

};
#endif // !Input_h
