#pragma once
#ifndef Vector2D_h
#define Vector2D_h
#include <iostream>
#include <string>

class Vector2D {
public:
	float X = 0;
	float Y = 0;
public:
	Vector2D(float x, float y){
		X = x;
		Y = y;
	}

	Vector2D(int x, int y) {
		X = (float)x;
		Y = (float)y;
	}

	Vector2D() {
		X = 0;
		Y = 0;
	}
public:

	//Addition
	inline Vector2D operator+(const Vector2D& v2) const {
		return Vector2D(v2.X + X, v2.Y + Y);
	}

	//Subtraction
	inline Vector2D operator-(const Vector2D& v2) const {
		return Vector2D(X - v2.X, Y - v2.Y);
	}

	//Multiplication
	inline Vector2D operator*(const float scalar) const {
		return Vector2D(X*scalar, Y*scalar);
	}

	void Log(std::string msg = "") {
		std::cout << msg << "(X,Y) = (" << X << "," << Y << ")" << std::endl;
	}

private:

};
#endif // !Vector2D_h
