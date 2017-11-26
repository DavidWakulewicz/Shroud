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
private:
	bool isRunning;

	std::shared_ptr<Camera> camera;
	std::shared_ptr<Player> player;
	std::shared_ptr<Keyboard> keyboard;
	std::unique_ptr<StateManager> stateManager;
	std::shared_ptr<Renderer> renderer;
	std::unique_ptr<World> world;

	float delta = 0;
	float updateDelta = 0;
	uint64_t current = 0;

	uint8_t updates = 0;
	uint16_t frames = 0;

	uint64_t lastTime = SDL_GetTicks();
	float timer = 0;

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
