#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <cstdint>

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	bool up;
	bool down;
	bool left;
	bool right;

	bool fullscreen;
	bool escape;

	void Update();

private:

};

#endif //KEYBOARD_H
