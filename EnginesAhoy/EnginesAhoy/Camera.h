#pragma once
#ifndef Camera_h
#define Camera_h
#include "Point.h"
#include "Vector2D.h"
#include "SDL.h"
#include "Engine.h"

class Camera {
public:

	inline int GetSceneWidth() { return m_SceneWidth; }
	inline int GetSceneHeight() { return m_SceneHeight; }

	inline void MoveX(float x) { m_Position.X = x; }
	inline void MoveY(float y) { m_Position.Y = y; }

	inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }

	inline SDL_Rect GetViewBox() { return m_ViewBox; }

	inline Vector2D GetPosition() { return m_Position; }

	inline void SetTarget(Point* target) { m_Target = target; }
	inline void SetSceneLimit(int w, int h) { m_SceneWidth = w; m_SceneHeight = h; }

	void Update(float dt);

private:
	Camera();

	Point* m_Target;
	Vector2D m_Position;

	SDL_Rect m_ViewBox;
	static Camera* s_Instance;
	int m_SceneWidth, m_SceneHeight;
};
#endif