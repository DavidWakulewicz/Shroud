#include "Renderer.h"

#include <SDL2/SDL_image.h>
#include <iostream>

Renderer::Renderer()
{
	// Create window
	// SDL_WINDOW_SHOWN flag is ignored according to document.
	// Might want to eventually use SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_INPUT_GRABBED
	// https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow("Shroud",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window could not be created!" << std::endl;
		exit(1);
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Renderer could not be created!" << std::endl;
		exit(1);
	}

	//Initialize renderer color (renderer, red, green, blue, alpha)
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Requires another library 'SDL_Image'
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << std::endl << std::endl << std::endl;
		std::cout << IMG_GetError() << std::endl;
		std::cout << std::endl << std::endl << std::endl;
		exit(2);
	}
}

Renderer::~Renderer()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
}

void Renderer::render()
{
	//Clear screen
	SDL_RenderClear(renderer);

	//Render texture to screen
	renderTiles();

	//Update screen
	SDL_RenderPresent(renderer);
}

void Renderer::renderTiles() {
	SDL_Rect destR;

	int x, y;
	int textureWidth, textureHeight;
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

	destR.w = textureWidth;
	destR.h = textureHeight;

	for (x = 0; x < SCREEN_WIDTH; x += textureWidth) {

		destR.x = x + xOffset;

		for (y = 0; y < SCREEN_HEIGHT; y += textureHeight) {
			//std::cout << "x position: " << x << "    y position: " << y << "\n";
			destR.y = y + yOffset;
			SDL_RenderCopy(renderer, texture, NULL, &destR);
		}
	}
}

void Renderer::SetXOffset(int offset) {
	xOffset = offset;
}

void Renderer::SetYOffset(int offset) {
	yOffset = offset;
}

int Renderer::GetXOffset() {
	return xOffset;
}

int Renderer::GetYOffset() {
	return yOffset;
}

SDL_Texture* Renderer::loadTexture(std::string path)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path.c_str()
			<< "! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL)
		{
			std::cout << "Unable to create texture from "
				<< path.c_str() << "! SDL Error: "
				<< SDL_GetError() << std::endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return texture;
}

void Renderer::setWindowTitle(std::string title)
{
	SDL_SetWindowTitle(window, title.c_str());
}
