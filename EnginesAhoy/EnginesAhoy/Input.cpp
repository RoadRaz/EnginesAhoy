#include "Input.h"
#include "Engine.h"

Input* Input::s_Instance = nullptr;

Input::Input() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT : 
				Engine::GetInstance()->Quit();
				break;
			case SDL_KEYDOWN:
				KeyDown();
				break;
			case SDL_KEYUP:
				KeyUp();
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseLeftButtonDown = (event.button.button == SDL_BUTTON_LEFT);
				mouseRightButtonDown = (event.button.button == SDL_BUTTON_RIGHT);
				mouseRightButtonUp = false;
				mouseLeftButtonUp = false;
				break;
			case SDL_MOUSEBUTTONUP:
				mouseLeftButtonUp = (event.button.button == SDL_BUTTON_LEFT);
				mouseRightButtonUp = (event.button.button == SDL_BUTTON_RIGHT);
				mouseRightButtonDown = false;
				mouseLeftButtonDown = false;
		}
	}
}



bool Input::GetMouseButtonDownLeft() {
	return mouseLeftButtonDown;
}

bool Input::GetMouseButtonDownRight() {
	return mouseRightButtonDown;
}

bool Input::GetMouseButtonUpLeft() {
	return mouseLeftButtonUp;
}

bool Input::GetMouseButtonUpRight() {
	return mouseRightButtonUp;
}

Vector2D Input::GetMousePosition() {
	int x =0, y=0;
	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	Vector2D mousePos = Vector2D(x,y);
	return mousePos;
}

bool Input::GetKeyDown(SDL_Scancode key) {
	return m_KeyStates[key] == 1;
}

bool Input::GetKeyUp(SDL_Scancode key) {
	return m_KeyStates[key] == 0;
}

void Input::KeyDown() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyUp() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}