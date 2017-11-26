#include "Game.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream>

#include "Renderer.h"
#include "Player.h"
#include "Keyboard.h"
#include "Camera.h"

#include "GameState.h"

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
		std::cout << "SDL Could not be initialized, exiting" << std::endl;
		exit(1);
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!"
			<< std::endl;
	}


	Key          = std::make_shared<Keyboard>();
	stateManager = std::make_unique<StateManager>();

	//Main loop flag
	isRunning = true;
}

Game::~Game()
{
	SDL_Quit();
}

void Game::Run()
{
	stateManager->Add<GameState>(shared_from_this());
	stateManager->Add<MenuState>(shared_from_this());
	stateManager->Change<GameState>();

	//While application is running
#if __EMSCRIPTEN__
        if (!isRunning)
        {
                emscripten_cancel_main_loop();
        }
        else
#else
	while (isRunning)
#endif
	{
		// Timer calculations
		current = SDL_GetTicks();
		delta = (current - lastTime) / 1000.0f;
		lastTime = current;

		updateDelta += delta;

		while (updateDelta >= SECONDS_PER_UPDATE) {
			// 'update' function that controls all updates (location of enemies, players, spells, input, etc.)
			update();
			updateDelta -= SECONDS_PER_UPDATE;
		}

		stateManager->Render();
	}
}

void Game::update() {

	//Event handler
	SDL_Event e;

	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			Stop();
			break;
		case SDL_MOUSEWHEEL:
			//if (e.wheel.y < 0)
			//{
			//	camera->ZoomIn();
			//}
			//else if (e.wheel.y > 0)
			//{
			//	camera->ZoomOut();
			//}
			break;
		}
	}

	Key->Update();
	stateManager->Update(SECONDS_PER_UPDATE);
}

void Game::Stop()
{
	isRunning = false;
}
