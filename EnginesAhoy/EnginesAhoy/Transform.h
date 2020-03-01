#pragma once
#ifndef Transform_h
#define Transform_h
#include "Vector2D.h"

class Transform {
public:
	float X;
	float Y;

public:
	Transform(float x, float y) {
		X = x;
		Y = y;
	}

	Transform() {
		X = 0;
		Y = 0;
	}

	void Log(std::string msg = "") {
		std::cout << msg << "(X,Y) = (" << X << "," << Y << ")" << std::endl;
	}

public:
	inline void TranslateX(float x) { X += x; }
	inline void TranslateY(float y) { Y += y; }
	inline void Translate(Vector2D v) {
		X += v.X;
		Y += v.Y;
	}
};
#endif // !Transform_h
