#include "Keyboard.h"

#include <SDL2/SDL_image.h>
//#include <iostream>

Keyboard::Keyboard()
{
	
}

Keyboard::~Keyboard()
{

}

void Keyboard::Update()
{
	const uint8_t *state = SDL_GetKeyboardState(NULL);

	// Movement
	up    = state[SDL_GetScancodeFromKey(SDLK_w)];
	down  = state[SDL_GetScancodeFromKey(SDLK_s)];
	left  = state[SDL_GetScancodeFromKey(SDLK_a)];
	right = state[SDL_GetScancodeFromKey(SDLK_d)];

	// Misc
	escape     = state[SDL_GetScancodeFromKey(SDLK_ESCAPE)];
	fullscreen = state[SDL_GetScancodeFromKey(SDLK_f)];

}