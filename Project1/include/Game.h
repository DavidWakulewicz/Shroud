#ifndef GAME_H
#define GAME_H

#include "Renderer.h"
#include <memory>
#include <SDL2/SDL.h>

class Game
{
public:
	Game();
	~Game();

	void run();
	void stop();
private:
	bool isRunning;

	std::unique_ptr<Renderer> renderer;

	void handleInput(SDL_Keycode);
};
#endif //GAME_H