#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void render();

	SDL_Texture* loadTexture(std::string);

	void setWindowTitle(std::string);
	void renderTiles();

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

private:
	//The window we'll be rendering to
	SDL_Window* window;

	//The window renderer
	SDL_Renderer* renderer;

	//Current displayed texture
	SDL_Texture* texture;
};

#endif //RENDERER_H