#pragma once
#ifndef IObject_h
#define IObject_h
#include "SDL.h"

class IObject {
public:
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;
};
#endif // !IObject_h
