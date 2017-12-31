#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <sstream>
#include <iostream>

#include "State.h"
#include "Keyboard.h"
#include "Renderer.h"
#include "Player.h"
#include "Game.h"

class Camera;
class Player;
class Renderer;

class MenuState;

class GameState : public State
{
public:
	using State::State;

	//~GameState() {};

	void Initialize()
	{
		player   = std::make_shared<Player>(game->Key);
		camera   = std::make_shared<Camera>(player);
		renderer = std::make_shared<Renderer>(camera, player);
		world    = std::make_unique<World>(renderer, player);

		camera->Bounds.Set(world->Width * Tile::WIDTH, world->Height * Tile::HEIGHT);

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
	};
	void Destroy() {};

	void Suspend() {};
	void Resume() {};

	void Update(float delta)
	{
		updates++;

		if (game->Key->Escape)
		{
			game->Stop();
		}
		else if (game->Key->Tab)
		{
			game->SetState<MenuState>();
		}
		else if (game->Key->Fullscreen)
		{
			renderer->ToggleFullscreen();
		}

		if (game->MouseWheel < 0)
		{
			camera->ZoomIn();
		}
		else if (game->MouseWheel > 0)
		{
			camera->ZoomOut();
		}

		player->Update();
		world->Collisions();

		camera->Update();

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
	};

	void Render()
	{
		frames++;

		renderer->Clear();

		world->Render();

		renderer->Render();
	};

private:
	uint8_t updates = 0;
	uint16_t frames = 0;
	float timer = 0;

	std::shared_ptr<Camera> camera;
	std::shared_ptr<Player> player;
	std::shared_ptr<Renderer> renderer;
	std::unique_ptr<World> world;
};

#endif //GAME_STATE_H
