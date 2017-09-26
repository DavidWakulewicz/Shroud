#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <memory>

#include "Renderer.h"

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

	float delta = 0;
	float updateDelta = 0;
	uint64_t current = 0;

	uint8_t updates = 0;
	uint16_t frames = 0;

	uint64_t lastTime = SDL_GetTicks();
	float timer = 0;

	const uint8_t UPDATES_PER_SECOND = 60;
	const float SECONDS_PER_UPDATE = 1.0 / UPDATES_PER_SECOND;


	void handleInput(SDL_Keycode);
};
#endif //GAME_H
