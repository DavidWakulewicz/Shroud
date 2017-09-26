#include "Renderer.h"

#include <SDL2/SDL_image.h>
#include <iostream>

Renderer::Renderer(std::shared_ptr<Camera> camera) : camera(camera)
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

	isFullscreen = false;

	camera->scale.Set(2.0f, 2.0f);
	camera->bounds.Set(WORLD_WIDTH, WORLD_HEIGHT);
	camera->size.Set(SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderSetScale(renderer, camera->scale.x, camera->scale.y);
}

Renderer::~Renderer()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
}

void Renderer::Render()
{
	//Clear screen
	SDL_RenderClear(renderer);

	SDL_RenderSetScale(renderer, camera->scale.x, camera->scale.y);

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

	for (x = 0; x < WORLD_WIDTH; x += textureWidth) {

		destR.x = x - camera->position.x;

		for (y = 0; y < WORLD_HEIGHT; y += textureHeight) {
			//std::cout << "x position: " << x << "    y position: " << y << "\n";
			destR.y = y - camera->position.y;
			SDL_RenderCopy(renderer, texture, NULL, &destR);
		}
	}
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

void Renderer::ToggleFullscreen()
{
	if (isFullscreen)
	{
		SDL_SetWindowFullscreen(window, 0);
		isFullscreen = false;
	}
	else
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		isFullscreen = true;
	}
}

void Renderer::ToggleFullscreen(uint32_t flag)
{
	SDL_SetWindowFullscreen(window, flag);
	if (flag & SDL_WINDOW_FULLSCREEN)
	{
		isFullscreen = false;
	}
	else
	{
		isFullscreen = true;
	}
}


void Renderer::SetWindowTitle(std::string title)
{
	SDL_SetWindowTitle(window, title.c_str());
}
