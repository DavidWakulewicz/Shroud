#include "Renderer.h"

#include <SDL2/SDL_image.h>
#include <iostream>

Renderer::Renderer() {}

//Renderer::Renderer(std::shared_ptr<Camera> camera) : camera(camera)
Renderer::Renderer(std::shared_ptr<Camera> camera, std::shared_ptr<Player> player) : camera(camera), player(player)
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
	camera->Size.Set(SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderSetScale(renderer, camera->Scale.x, camera->Scale.y);

	SDL_Texture* texture = this->loadTexture(player->Texture);
	if (texture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		exit(1);
	}
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

void Renderer::Clear() 
{
	SDL_RenderClear(renderer);
}

void Renderer::AddToFrame(std::shared_ptr<Entity> entity) 
{
	SDL_Rect dRect;

	dRect.x = entity->Pos.x - camera->Pos.x;
	dRect.y = entity->Pos.y - camera->Pos.y;
	dRect.w = entity->Bounds.x;
	dRect.h = entity->Bounds.y;

	if (dRect.x > -(entity->Bounds.x / camera->Scale.x * 3) &&
	    dRect.y > -(entity->Bounds.y / camera->Scale.y * 3) && 
	    dRect.x < (SCREEN_WIDTH / camera->Scale.x) + (entity->Bounds.x / camera->Scale.x * 3) &&
	    dRect.y < (SCREEN_HEIGHT / camera->Scale.y) + (entity->Bounds.y / camera->Scale.y * 3))
	{	
		SDL_RenderCopy(renderer, textures[entity->Texture], NULL, &dRect);
	}
}

void Renderer::Render()
{
	// Render player to screen
	this->AddToFrame(player);

	//Update screen
	SDL_RenderSetScale(renderer, camera->Scale.x, camera->Scale.y);
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

uint32_t Renderer::GetWindowFormat() {
	return SDL_GetWindowPixelFormat(window);
}
