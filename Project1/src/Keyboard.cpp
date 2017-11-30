#include "Keyboard.h"

#include <SDL2/SDL.h>

void Keyboard::Update()
{
	const uint8_t *state = SDL_GetKeyboardState(NULL);

	// Movement
	Up    = state[SDL_GetScancodeFromKey(SDLK_w)];
	Down  = state[SDL_GetScancodeFromKey(SDLK_s)];
	Left  = state[SDL_GetScancodeFromKey(SDLK_a)];
	Right = state[SDL_GetScancodeFromKey(SDLK_d)];
	Q     = state[SDL_GetScancodeFromKey(SDLK_q)];
	Enter = state[SDL_GetScancodeFromKey(SDLK_RETURN)];
	Tab   = state[SDL_GetScancodeFromKey(SDLK_TAB)];

	// Misc
	Escape     = state[SDL_GetScancodeFromKey(SDLK_ESCAPE)];
	Fullscreen = state[SDL_GetScancodeFromKey(SDLK_f)];

}
