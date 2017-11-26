#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <memory>

#include "StateManager.h"
#include "Renderer.h"
#include "Keyboard.h"
#include "Player.h"
#include "World.h"

class Camera;
class Player;
class Keyboard;
class Renderer;

class Game : public std::enable_shared_from_this<Game>
{
public:
	Game();
	~Game();

	void Run();
	void Stop();

	template <typename T>
	void SetState();

	std::shared_ptr<Keyboard> Key;
private:
	bool isRunning;

	std::unique_ptr<StateManager> stateManager;

	float delta = 0;
	float updateDelta = 0;
	uint64_t current = 0;

	uint64_t lastTime = SDL_GetTicks();

	const uint8_t UPDATES_PER_SECOND = 60;
	const float SECONDS_PER_UPDATE = 1.0 / UPDATES_PER_SECOND;

	void update();
	void handleInput(SDL_Keycode);
};

template <typename T>
void Game::SetState()
{
	stateManager->Change<T>();
}

#endif //GAME_H
