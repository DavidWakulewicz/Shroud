#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>

#include "State.h"
#include "Keyboard.h"
#include "Renderer.h"
#include "Player.h"
#include "Game.h"

class Camera;
class Player;
class Keyboard;
class Renderer;

class MenuState;

class GameState : public State
{
public:
	using State::State;

	//~GameState() {};

	void Initialize() {};
	void Destroy() {};

	void Suspend() {};
	void Resume() {};

	void Update()
	{
		std::cout << "GameState" << std::endl;
		//player->Update();
		//camera->Update();

		//if (keyboard->Q)
		//{
		//	game->SetState<MenuState>();
		//}
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
	using State::State;

	//~MenuState() {};

	void Initialize() {};
	void Destroy() {};

	void Suspend() {};
	void Resume() {};

	void Update()
	{
		std::cout << "MenuState" << std::endl;
		//if (keyboard->Q)
		//{
		//	game->SetState<GameState>();
		//}
	};
	void Render() {};

private:
	std::shared_ptr<Keyboard> keyboard;
};

#endif //GAME_STATE_H
