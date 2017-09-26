#include "Game.h"

#include <iostream>
#include <sstream>

#include "Renderer.h"

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
		std::cout << "SDL Could not be initialized, exiting" << std::endl;
		exit(1);
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}


	camera = std::make_shared<Camera>();
	renderer = std::make_unique<Renderer>(camera);

	//Load PNG texture
	SDL_Texture* texture = renderer->loadTexture("res/tiles/SpawnTileWall.png");
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

void Game::run()
{
	//While application is running
	while (isRunning)
	{
		// Timer calculations
		current = SDL_GetTicks();
		delta = (current - lastTime) / 1000.0f;
		lastTime = current;

		updateDelta += delta;

		while (updateDelta >= SECONDS_PER_UPDATE) {
			// Future call to 'update' function that updates location of enemies, players, spells, etc.
			updates++;
			updateDelta -= SECONDS_PER_UPDATE;

			//Event handler
			SDL_Event e;

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				switch(e.type)
				{
				case SDL_QUIT:
					stop();
					break;
				case SDL_KEYDOWN:
					handleInput(e.key.keysym.sym);
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

			camera->Update();
		}

		// Future call to 'render' function here, will control all rendering (RenderClear, RenderCopy, RenderPresent will get moved there)
		frames++;

		renderer->Render();

		timer += delta;
		if (timer > 1.0f) {
			std::ostringstream title;
			title << "Shroud" << "  |  "
			        << static_cast<int>(updates) << " UPS  "
			        << frames << " FPS";
			renderer->SetWindowTitle(title.str());

                        timer -= 1.0f;
                        frames = 0;
			updates = 0;
		}
	}
}

void Game::handleInput(SDL_Keycode key)
{
	// PLAYER MOVEMENT TODO
	// Should create a map of keys with true/false values
	// default false
	// set to true when key is pressed
	// set to false when key is unpressed
	// -- should prevent the ~second delay after a key is initially held down to signal continuous movement
	// -- should also allow for 'double movement' when, for example, 'W' and 'A' keys are pressed together
	// check true/false values when updating player position instead
	switch (key)
	{
	case SDLK_ESCAPE:
		stop();
		break;
	case SDLK_w:
		camera->position.y -= 10;
		break;
	case SDLK_s:
		camera->position.y += 10;
		break;
	case SDLK_a:
		camera->position.x -= 10;
		break;
	case SDLK_d:
		camera->position.x += 10;
		break;
	case SDLK_f:
		renderer->ToggleFullscreen();
		break;
	}
	return;
}

void Game::stop()
{
	isRunning = false;
}
