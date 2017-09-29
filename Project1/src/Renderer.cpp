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

	camera->Scale.Set(2.0f, 2.0f);
	camera->Bounds.Set(WORLD_WIDTH, WORLD_HEIGHT);
	camera->Size.Set(SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderSetScale(renderer, camera->Scale.x, camera->Scale.y);
}

Renderer::~Renderer()
{
	for (auto texture : textures)
	{
		SDL_DestroyTexture(texture.second);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
}

void Renderer::Render()
{
	//Clear screen
	SDL_RenderClear(renderer);

	SDL_RenderSetScale(renderer, camera->Scale.x, camera->Scale.y);

	SDL_Rect dRect;

	//Render texture to screen
	for (auto tile : tiles)
	{
		dRect.x = tile.Pos.x - camera->Pos.x;
		dRect.y = tile.Pos.y - camera->Pos.y;
		dRect.w = tile.Bounds.x;
		dRect.h = tile.Bounds.y;

		if (dRect.x > -(tile.Bounds.x / camera->Scale.x * 3) &&
		    dRect.y > -(tile.Bounds.y / camera->Scale.y * 3) && 
		    dRect.x < (SCREEN_WIDTH / camera->Scale.x) + (tile.Bounds.x / camera->Scale.x * 3) &&
		    dRect.y < (SCREEN_HEIGHT / camera->Scale.y) + (tile.Bounds.y / camera->Scale.y * 3))
		{
			SDL_RenderCopy(renderer, textures[tile.Texture], NULL, &dRect);
		}


	}

	//Update screen
	SDL_RenderPresent(renderer);
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
		textures[path] = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (textures[path] == NULL)
		{
			std::cout << "Unable to create texture from "
				<< path.c_str() << "! SDL Error: "
				<< SDL_GetError() << std::endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	for (int x = 0; x < WORLD_WIDTH; x += Tile::WIDTH) {
		for (int y = 0; y < WORLD_HEIGHT; y += Tile::HEIGHT) {
			uint64_t xPos = x - camera->Pos.x;
			uint64_t yPos = y - camera->Pos.y;

			Tile tile(path);
			tile.Pos.x = xPos;
			tile.Pos.y = yPos;
			tiles.push_back(tile);
		}
	}

	return textures[path];
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
