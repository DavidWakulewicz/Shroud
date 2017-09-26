#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>

#include "Camera.h"

class Renderer
{
public:
	Renderer(std::shared_ptr<Camera>);
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

	const int64_t WORLD_WIDTH = SCREEN_WIDTH * 5;
	const int64_t WORLD_HEIGHT = SCREEN_HEIGHT * 5;

private:
	//The window we'll be rendering to
	SDL_Window* window;

	//The window renderer
	SDL_Renderer* renderer;

	//Current displayed texture
	SDL_Texture* texture;

	std::shared_ptr<Camera> camera;

	void renderTiles();
};

#endif //RENDERER_H
