#pragma once
#ifndef Layer_h
#define Layer_h

class Layer {

public:
	virtual void Render() = 0;
	virtual void Update() = 0;

};
#endif // Layer_h