#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

Camera::Camera() {
	m_ViewBox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; 
	m_SceneHeight = SCREEN_HEIGHT;
	m_SceneWidth = SCREEN_WIDTH;
}

void Camera::Update(float dt){

	if (m_Target != nullptr) {
		m_ViewBox.x = m_Target->X - m_SceneWidth / 2;
		m_ViewBox.y = m_Target->Y - m_SceneHeight / 2;

		if (m_ViewBox.x < 0) {
			m_ViewBox.x = 0;
		}

		if (m_ViewBox.y < 0) {
			m_ViewBox.y = 0;
		}

		if (m_ViewBox.x > (2 * m_SceneWidth - m_ViewBox.w)) {
			m_ViewBox.x = (2 * m_SceneWidth - m_ViewBox.w);
		}

		if (m_ViewBox.y > (m_SceneHeight - m_ViewBox.h)) {
			m_ViewBox.y = (m_SceneHeight - m_ViewBox.h);
		}

		m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
	}

}

