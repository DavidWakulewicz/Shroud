#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>

#include "State.h"
#include "Keyboard.h"
#include "Renderer.h"
#include "Player.h"

class Camera;
class Player;
class Keyboard;
class Renderer;

class MenuState;

class GameState : public State
{
public:
	~GameState() {};

	void Initialize() {};
	void Destroy() {};

	void Suspend() {};
	void Resume() {};

	void Update()
	{
		player->Update();
		camera->Update();

		if (keyboard->Q)
		{
			game->SetState<MenuState>();
		}
	};
	void Render() {};

private:
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Player> player;
	std::shared_ptr<Keyboard> keyboard;
	std::unique_ptr<Renderer> renderer;
};

class MenuState : public State
{
public:
	~MenuState() {};

	void Initialize() {};
	void Destroy() {};

	void Suspend() {};
	void Resume() {};

	void Update()
	{
		if (keyboard->Q)
		{
			game->SetState<GameState>();
		}
	};
	void Render() {};
};

#endif //GAME_STATE_H
