#include "World.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

World::World(std::shared_ptr<Renderer> renderer) : renderer(renderer)
{
	uint32_t format = renderer->GetWindowFormat();
	SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);

	uint32_t wall = SDL_MapRGB(mappingFormat, 0x00, 0x00, 0x00);
	uint32_t floor = SDL_MapRGB(mappingFormat, 0x00, 0xA9, 0xFF);
	uint32_t steps = SDL_MapRGB(mappingFormat, 0x00, 0x6E, 0xA5);

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load("res/levels/world.png");
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << "res/levels/world.png"
			<< "! SDL_image Error: " << IMG_GetError() << std::endl;

		return;
	}

	SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, format, static_cast<uint32_t>(NULL));
	if (formattedSurface == NULL)
	{
		std::cout << "Unable to convert loaded surface to display format! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	Width = formattedSurface->w;
	Height = formattedSurface->h;
	
	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			int i = (x % Width) + (y * Height);

			std::string path;
			if (static_cast<uint32_t*>(formattedSurface->pixels)[i] == wall)
			{
				path = "res/tiles/SpawnTileWall.png";
			}
			else if (static_cast<uint32_t*>(formattedSurface->pixels)[i] == floor)
			{
				path = "res/tiles/SpawnTile.png";
			}
			else if (static_cast<uint32_t*>(formattedSurface->pixels)[i] == steps)
			{
				path = "res/tiles/FootStepNorth.png";
			}

			Tile tile(path);
			tile.Pos.x = x * Tile::WIDTH;
			tile.Pos.y = y * Tile::HEIGHT;
			Tiles.push_back(tile);
		}
	}

	SDL_FreeSurface(formattedSurface);
}

// Multiple maps? Potentially split into smaller 'Map' classes
// Have something to track the 'active map' then the for loop for the tiles would just be 'for tile : activeMap.Tiles) {...'
void World::Render() {
	renderer->Clear();
	
	for (auto tile : Tiles) {
		renderer->AddToFrame(tile);
	}

	renderer->Render();
}
