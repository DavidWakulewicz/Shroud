#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "Camera.h"
#include "Tile.h"
#include "World.h"

class Renderer
{
public:
	Renderer(std::shared_ptr<Camera>, std::shared_ptr<Player>);
	~Renderer();

	void Render();

	SDL_Texture* loadTexture(std::string);

	bool isFullscreen;
	void ToggleFullscreen();
	void ToggleFullscreen(uint32_t);

	void SetWindowTitle(std::string);

	//Screen dimension constants
	const int64_t SCREEN_WIDTH = 640;
	const int64_t SCREEN_HEIGHT = 480;

private:
	std::unique_ptr<World> world;

	//The window we'll be rendering to
	SDL_Window* window;

	//The window renderer
	SDL_Renderer* renderer;

	//Current displayed texture
	std::unordered_map<std::string, SDL_Texture*> textures;

	std::shared_ptr<Camera> camera;
	std::shared_ptr<Player> player;

	std::vector<Tile> tiles;
};

#endif //RENDERER_H
