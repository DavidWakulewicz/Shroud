#ifndef KEYBOARD_H
#define KEYBOARD_H

//#include <SDL2/SDL.h>
//#include <string>
#include <memory>
#include "Camera.h"

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	int8_t up;
	int8_t down;
	int8_t left;
	int8_t right;

	int8_t fullscreen;
	int8_t escape;

	void Update();

private:

};

#endif //KEYBOARD_H
