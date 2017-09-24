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

	void SetXOffset(int);
	void SetYOffset(int);

	int GetXOffset();
	int GetYOffset();

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

	// Screen offsets
	int xOffset = 0;
	int yOffset = 0;
};

#endif //RENDERER_H