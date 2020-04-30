#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include "Input.h"
#include "GameObject.h"
#include "TextureManager.h"
#include <vector>
#include "Camera.h"

using TextureIdList = std::vector<std::string>;

enum ButtonState {NORMAL=0, HOVER=1, PRESSED=2};

class Button : public GameObject{
public:
	Button(int x, int y, void(*callback) (), TextureIdList texIds) : GameObject(new Properties()) {
		m_Tf = new Transform(x, y);
		m_Callback = callback;
		m_TextureIds = texIds;
		m_Tf->TextureID = m_TextureIds[NORMAL];
		TextureManager::GetInstance()->QueryTexture(m_Tf->TextureID, &m_Tf->Width, &m_Tf->Height);
		m_Shape = { (int)m_Tf->X, (int)m_Tf->Y, m_Tf->Width, m_Tf->Height };

	}

	~Button() {
		m_TextureIds.clear();
		m_TextureIds.shrink_to_fit();
	}

	virtual void Clean() override {
		for (auto id : m_TextureIds) {
			//TextureManager::GetInstance()->DestroyTexture();
		}

		m_TextureIds.clear();
		m_TextureIds.shrink_to_fit();
	}

	virtual void Update(float dt) override {
		Vector2D mousePos = Input::GetInstance()->GetMousePosition();
		SDL_Point point = { mousePos.X, mousePos.Y };
		
		if (SDL_PointInRect(&point, &m_Shape)) {
			if (Input::GetInstance()->GetMouseButtonDownLeft() && m_IsReleased) {
				//m_Callback();
				m_IsReleased = false;
				m_Tf->TextureID = m_TextureIds[PRESSED];

			}
			else if (!Input::GetInstance()->GetMouseButtonDownLeft()) {
				m_IsReleased = true;
				m_Tf->TextureID = m_TextureIds[HOVER];
			}
		}
		else {
			m_Tf->TextureID = m_TextureIds[NORMAL];
		}
	}

	virtual void Draw() override {
		TextureManager::GetInstance()->Draw(m_Tf->TextureID, m_Tf->X + Camera::GetInstance()->GetPosition().X, m_Tf->Y + Camera::GetInstance()->GetPosition().Y, m_Tf->Width, m_Tf->Height);
	}

private:
	Transform* m_Tf;
	void (*m_Callback) ();
	TextureIdList m_TextureIds;
	SDL_Rect m_Shape;
	bool m_IsReleased = true;
};
#endif