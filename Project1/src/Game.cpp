#include "Game.h"

#include <iostream>
#include <sstream>

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


	keyboard     = std::make_shared<Keyboard>();
	player       = std::make_shared<Player>(keyboard);
	camera       = std::make_shared<Camera>(player);
	renderer     = std::make_unique<Renderer>(camera);
	stateManager = std::make_unique<StateManager>();

	//Load PNG texture
	SDL_Texture* texture = renderer->loadTexture("res/tiles/SpawnTileWall.png");
	if (texture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		exit(1);
	}
	texture = renderer->loadTexture("res/tiles/SpawnTile.png");
	if (texture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		exit(1);
	}
	texture = renderer->loadTexture("res/tiles/FootStepNorth.png");
	if (texture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		exit(1);
	}

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
	while (isRunning)
	{
		// Timer calculations
		current = SDL_GetTicks();
		delta = (current - lastTime) / 1000.0f;
		lastTime = current;

		updateDelta += delta;

		while (updateDelta >= SECONDS_PER_UPDATE) {
			// 'update' function that controls all updates (location of enemies, players, spells, input, etc.)
			update();
			stateManager->Update();
			updates++;
			updateDelta -= SECONDS_PER_UPDATE;
		}

		//'render' function will control all rendering
		renderer->Render();
		frames++;

		timer += delta;
		if (timer > 1.0f) {
			std::ostringstream title;
			title << "Shroud" << "  |  "
			        << static_cast<int>(updates) << " UPS  "
			        << frames << " FPS "
			        << delta * 1000.0f << " ms";
			renderer->SetWindowTitle(title.str());

                        timer -= 1.0f;
                        frames = 0;
			updates = 0;
		}
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
			if (e.wheel.y < 0)
			{
				camera->ZoomIn();
			}
			else if (e.wheel.y > 0)
			{
				camera->ZoomOut();
			}
			break;
		}
	}

	keyboard->Update();

	if (keyboard->Escape)     Stop();
	if (keyboard->Fullscreen) renderer->ToggleFullscreen();
	if (keyboard->Q && stateManager->Is<MenuState>())
	{
		stateManager->Change<GameState>();
	}
	else if (keyboard->Q && stateManager->Is<GameState>())
	{
		stateManager->Change<MenuState>();
	}

	stateManager->Update();
}

void Game::Stop()
{
	isRunning = false;
}
