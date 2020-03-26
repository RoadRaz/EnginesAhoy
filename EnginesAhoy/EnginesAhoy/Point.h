#pragma once
#ifndef Point_h
#define Point_h
#include <iostream>
#include <string>

class Point {
public:
public:
	float X = 0;
	float Y = 0;
public:
	Point(float x, float y) {
		X = x;
		Y = y;
	}

	Point() {
		X = 0;
		Y = 0;
	}
public:

	//Addition
	inline Point operator+(const Point& p2) const {
		return Point(p2.X + X, p2.Y + Y);
	}

	//Subtraction
	inline Point operator-(const Point& p2) const {
		return Point(X - p2.X, Y - p2.Y);
	}

	inline friend Point operator-=(Point& p1, const Point& p2) {
		p1.X -= p2.X;
		p1.Y -= p2.Y;
		return p1;
	}

	inline friend Point operator+=(Point& p1, const Point& p2) {
		p1.X += p2.X;
		p1.Y += p2.Y;
		return p1;
	}

	//Multiplication
	inline Point operator*(const float scalar) const {
		return Point(X * scalar, Y * scalar);
	}

	void Log(std::string msg = "") {
		std::cout << msg << "(X,Y) = (" << X << "," << Y << ")" << std::endl;
	}
private:

};
#endif //Point_h