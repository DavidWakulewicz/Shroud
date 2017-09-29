#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <cstdint>

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	bool Up;
	bool Down;
	bool Left;
	bool Right;

	bool Fullscreen;
	bool Escape;

	void Update();

private:

};

#endif //KEYBOARD_H
