#pragma once
#ifndef GameObject_h
#define GameObject_h
#include "IObject.h"
#include "Transform.h"
#include "Point.h"

struct Properties {

public:
	Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		TextureID = textureID;
		X = x;
		Y = y;
		Height = height;
		Width = width;
		Flip = flip;

	}

public:
	std::string TextureID;
	int Width, Height;
	float X, Y;
	SDL_RendererFlip Flip;
};

class GameObject {

public :
	GameObject(Properties* props) : m_TextureID(props->TextureID), m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip) {
		m_Transform = new Transform(props->X, props->Y);

		float px = props->X + props->Width / 2;
		float py = props->Y + props->Height / 2;
		m_Origin = new Point(px, py);
	}

	inline Point* GetOrigin() { return m_Origin; }

	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

protected:
	Point* m_Origin;
	Transform* m_Transform;
	int m_Width, m_Height;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;

};
#endif // !GameObject_h
